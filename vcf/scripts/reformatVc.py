#!/usr/bin/env python
#
# Author: Marcello Pietrobon
#

"""
"""

import sys
import os
import os.path
import shutil
import filecmp
import ConfigParser
import re
from copy import copy # to copy(Option.TYPE_CHECKER)
from optparse import OptionParser, Option, OptionValueError

backupFiles = False

modules ={}


# globals
compilerVc6  = 'vc6'
compilerVc70 = 'vc70'
compilerVc71 = 'vc71'
compilerIcl7 = 'icl7'
g_default_config = "reformatVc.ini"
g_default_section = "vcfscript"
g_default_allProjects = './build/vc60/vcfAllProjects.dsw'
g_default_allExamples = './Examples/Examples.dsw'
g_dependenciesWorkspace = './build/vc60/vcfAllLibs.dsw'
g_dependencyFilterExamplesProject = 'examples/'

# ( hardcoded )
g_tableFilterWorkspacesCreation = {}
g_tableFilterWorkspacesCreation[ 'vcfallprojects' ] = './'
g_tableFilterWorkspacesCreation[ 'examples' ] = 'examples/'

# ( hardcoded )
g_gtkLibrariesList = [ 'GraphicsKitGtk', 'ApplicationKitGtk' ] # Remark: this list must follow an increasing dependency order


# deleteLineString               = '# PROP Scc_'   # obsolete


#enum AppType
enumAppTypeNone = 0
enumAppTypeExe  = 1
enumAppTypeDll  = 2
enumAppTypeLib  = 3

enum_ADD_NONE        = 0
enum_ADD_CPP         = 1
enum_SUBTRACT_CPP    = 2
enum_ADD_LINK32      = 3
enum_SUBTRACT_LINK32 = 4
enum_ADD_LIB32       = 5
enum_SUBTRACT_LIB32  = 6
enum_ADD_BSC32       = 7

#enumStatic  = { 'static' : 1, 'dynamic' : 2 }

re_trueproject = re.compile( r'# Microsoft Developer Studio Project File - Name="(?P<trueProjectName>[a-zA-Z0-9_\- \\/.]*?)" - Package Owner=<([0-9]+)>' )
re_output_or_intermed_dir = re.compile( r'(^# PROP (Output|Intermediate)_Dir "(?P<subdir>[a-zA-Z0-9_\- $\(\)\\/.]*?)")' )
re_output_dir = re.compile( r'^# PROP Output_Dir "(?P<subdir>[a-zA-Z0-9_\- $\(\)\\/.]*?)"' )
re_intermed_dir = re.compile( r'^# PROP Intermediate_Dir "(?P<subdir>[a-zA-Z0-9_\- $\(\)\\/.]*?)"' )
#re_configuration = re.compile( r'"\$\(CFG\)"(\s+)==(\s+)"(?P<projectName>\w+)(\s+)-(\s+)(?P<platform>\w+)(\s+)(?P<configName>\w+)"' )
re_configuration = re.compile( r'"\$\(CFG\)"(\s+)==(\s+)"(?P<projectName>\w+)(\s+)-(\s+)(?P<platform>(\w+\s+)+)(?P<configName>\w+)"' )

re_LIB32_static             = re.compile( r'^LIB32\s*=' )
re_PROP                     = re.compile( r'^# PROP' )
re_ADD                      = re.compile( r'^# ADD' )
re_ADD_CPP                  = re.compile( r'^# ADD CPP' )
re_ADD_CPP_ALL              = re.compile( r'^# ADD (BASE |)CPP' )
re_ADD_CPP_BASE             = re.compile( r'^# ADD BASE CPP' )
re_SUBTRACT_CPP             = re.compile( r'^# SUBTRACT CPP' )
re_ADD_LINK32               = re.compile( r'^# ADD LINK32' )
re_ADD_LINK32_ALL           = re.compile( r'^(# ADD (BASE |)LINK32)' )
re_ADD_LINK32_BASE          = re.compile( r'^# ADD BASE LINK32' )
re_SUBTRACT_LINK32          = re.compile( r'^# SUBTRACT LINK32' )
re_ADD_LIB32                = re.compile( r'^# ADD LIB32' )
re_ADD_LIB32_ALL            = re.compile( r'^# ADD (BASE |)LIB32' )
re_ADD_LIB32_BASE           = re.compile( r'^# ADD BASE LIB32' )
re_SUBTRACT_LIB32           = re.compile( r'^# SUBTRACT LIB32' )
re_ADD_BSC32                = re.compile( r'^# ADD BSC32' )
re_ADD_BSC32_ALL            = re.compile( r'^# ADD (BASE |)BSC32' )
re_ADD_BSC32_BASE           = re.compile( r'^# ADD BASE BSC32' )
re_option_out_dir           = re.compile( r'/out:"(?P<subdir>[a-zA-Z0-9_\- $\(\)\\/.]*?)"' )


################################################################################
class StringUtils:
    """Utilities class"""
    def replace( text, str, replac ):
        i = text.find( str )
        if ( i != -1 ):
            ls = len(str)
            text = text[:i] + replac + text[i+ls:]
        return text
    replace = staticmethod(replace)

    def stripSpacesInExcess( line ):
        # eliminates double spaces
        ( ln, crlf ) = StringUtils.getEol( line )
        if ( 0 < ln and ( line[ln-1] == ' ' or line[ln-1] == '\t' ) ):
            line = line[:ln-1]
        line = re.sub( '\s+', ' ', line )
        # also this would do the work
        # line = ' '.join( line.split() )

        # eliminates space at the eol
        ln = len( line )
        if ( 0 < ln and ( line[ln-1] == ' ' or line[ln-1] == '\t' ) ):
            line = line[:ln-1]

        line += crlf
        return line
    stripSpacesInExcess = staticmethod(stripSpacesInExcess)

    def getEol( line ):
        ln = len( line )
        if ( 0 < ln and line[ln-1] == '\n' ):
            ln -= 1
            if ( 0 < ln and line[ln-1] == '\r' ):
                ln -= 1
        return ( ln, line[ln:] )
    getEol = staticmethod(getEol)

    def trimCommas( text ):
        #if surrounded by commas, removes them
        ld = len( text )
        if ( 1 < ld ):
            if ( ( text[0] == '\'' and text[-1] == '\'' ) or ( text[0] == '\"' and text[-1] == '\"' ) ):
                text = text[1:-1]
        return text
    trimCommas = staticmethod(trimCommas)

    def stripComment( text, rightTrim = True ):
        #remove anything after tha last '#' unless it is before a comma
        i = text.find( '#' )
        if ( i != -1 ):
            # trivial implementaion disabled
            if ( False ):
                c = max(text.rfind('\''), text.rfind('\"') )
                if ( c < q ):
                    text = text[:q]
                    text = text.rstrip()

            t = text
            lt = len(t)
            pound  = 0
            apex   = False
            comma  = False
            escaped = False
            i = 0
            while ( i < lt ):
                c = t[i]
                if ( c == '\n' ):
                    break
                elif ( c == '#' ):
                    if ( not escaped ):
                        if ( not comma and not apex ):
                            pound += 1
                            break
                    escaped = False
                elif ( c == '\'' ):
                    if ( not escaped ):
                        if ( comma ):
                            raise Exception ( 'Unbalanced commas in text: ' + text )
                        apex = not apex
                    escaped = False
                elif ( c == '\"' ):
                    if ( not escaped ):
                        if ( comma ):
                            raise Exception ( 'Unbalanced apexes in text: ' + text )
                        comma = not comma
                    escaped = False
                elif ( c == '\\' ):
                    escaped = not escaped
                else:
                    escaped = False

                i += 1
                continue

            if ( pound ):
                text = text[:i]
                if ( rightTrim ):
                    text = text.rstrip()
        return text
    stripComment = staticmethod(stripComment)


################################################################################
class FileUtils:
    def backup( filename ):
        if ( len(filename) > 4 and filename[-4:] == '.bak' ):
                # does not backup backup files
            pass
        else :
            bakname = filename + '.bak'
            if ( os.path.exists( bakname ) ) :
                print 'removing ' + bakname
                os.remove( bakname )
                shutil.copyfile( fullname, bakname )
    backup = staticmethod(backup)

    def replaceFile( source, destination ):
        changedFiles   = 0
        unchangedFiles = 0
        createdFiles   = 0

        if ( not os.path.exists( source ) ) :
            raise Exception( 'replaceFile() - the source file \'%s\' does not exist!' % source )

        if ( os.path.exists( destination ) ) :
            if ( not filecmp.cmp( source, destination ) ):
                # some changes
                os.remove( destination )
                os.rename( source, destination )
                changedFiles += 1
            else:
                # no changes
                os.remove( source )
                unchangedFiles += 1

            #if ( False ):
            #    shutil.copyfile( source, destination )
            #    if ( os.path.exists( source ) ) :
            #        os.remove( source ) # ' OSError: [Errno 13] Permission denied ' Why ???
        else:
            createdFiles += 1
            os.rename( source, destination )

        return ( changedFiles, unchangedFiles, createdFiles )
    replaceFile = staticmethod(replaceFile)


    def sameDrive( path1, path2 ):
        ( d1, p1 ) = os.path.splitdrive( path1 )
        ( d2, p2 ) = os.path.splitdrive( path2 )
        if ( len(d1) and len(d2) and d1 != d2 ):
            return False
        return True
    sameDrive = staticmethod(sameDrive)

    def normPathSimple( path, unixStyle, keepFirstDot=False ):
        # this function is probaly going to slowly replace os.path.normpath()
        if ( unixStyle ):
            path = path.replace("\\", "/")
            path = path.replace("//", "/")      # eliminates doubles
        else:
            path = path.replace("/", "\\")
            path = path.replace("\\\\", "\\")   # eliminates doubles
        return path
    normPathSimple = staticmethod(normPathSimple)

    def normPath( path, unixStyle, keepFirstDot=False ):
        # gets rid of exceding './' ( included the first ) and of the final '/'
        hasCurr = False
        if ( unixStyle ):
            curr = './'
        else:
            curr = '.\\'

        # we need to do this first otherwise problems under cygwin when unixStyle=True but the path starts with r'.\'
        path = FileUtils.normPathSimple( path, unixStyle )

        if ( path == '.' or path == curr ):
            if ( keepFirstDot ):
                path = curr
            else:
                path = ''
            return path

        if ( path and path[0] == '.' ):
            if ( 1 < len(path) and path[1] in '/\\' ):
                hasCurr = True
            
        path = os.path.normpath( path ) # eliminates the first './' unless it is just that

        if ( hasCurr and keepFirstDot ):
            path = curr + path

        # again unfortunately, because of os.path.normpath(). In the future implement just normPathSimple
        path = FileUtils.normPathSimple( path, unixStyle )

        return path
    normPath = staticmethod(normPath)

    def normDir( path, unixStyle, keepFirstDot=False ):
        if ( unixStyle ):
            sep = '/'
            curr = './'
        else:
            sep = '\\'
            curr = '.\\'

        if ( path == '.' or path == curr ):
            if ( keepFirstDot ):
                path = curr
            else:
                path = ''
            return path

        #path += '/' # this to make sure that os.path.dirname doesn't cut away the last part of the path
        #path = os.path.dirname( path )
        if ( path != '' ):
            path += sep # this to make sure that os.path.dirname doesn't cut away the last part of the path
        path = FileUtils.normPath( path, unixStyle, keepFirstDot )
        if ( path ):
            path += sep # we consider normalized a path with the slash at the end
        return path
    normDir = staticmethod(normDir)

    def getNormSep( unixStyle ):
        c = '/'
        if ( not unixStyle ):
            c = '\\'
        return c
    getNormSep = staticmethod(getNormSep)

    def absolutePath( workingpath, path, unixStyle ):
        if ( len( path ) == 0 ):
            path = './'
            #if ( we want to keep this raise Exception we need to change FileUtils::normDir
            #raise Exception( 'absolutePath() relative path is empty' )

        workingpath = workingpath.replace("\\", "/")
        workingpath = workingpath.replace("//", "/")   # eliminates doubles
        wp = workingpath.find( './' )
        if ( wp != -1 ):
            raise Exception( 'absolutePath() malformed working path \'%s\' ' % workingpath )
            #workingpath = FileUtils.absolutePath( '', workingpath, unixStyle ) # this might solve well the problem: will check later

        if ( len ( workingpath ) == 0 ):
            workingpath = app.getcwd()
            workingpath = os.path.normpath( workingpath )

        path = path.replace("\\", "/")
        path = path.replace("//", "/")   # eliminates doubles

        workingpath = workingpath.replace("\\", "/")    # again, because of os.path.normpath() %%%
        workingpath = workingpath.replace("//", "/")    # eliminates doubles

        if ( len ( workingpath ) == 0 ):
            raise Exception( 'absolutePath() couldn\'t get any working path ' )

        # extract current drive
        if ( not FileUtils.sameDrive( workingpath, path ) ):
            raise Exception( 'absolutePath() not same drive for %s and %s! ' % ( workingpath, path ) )

        # makes sure we don't add an absolute path to another one
        ( wdrive, wpath ) = os.path.splitdrive( workingpath )
        ( rdrive, rpath ) = os.path.splitdrive( path )

        if ( rpath[0] == '/' ):
                # path is already an absolute path let's just add the drive
            if ( len( rdrive ) == 0 ):
                path = wdrive + path
                return path

        rp = rpath.find( '../' )
        if ( rp != -1 ):
            rpath = path
            wpath = wpath
            if ( wpath[-1] == '/' ):
                wpath = wpath[:-1] # because we are going to wpath.rfind( sep )
            while ( rp != -1 ):
                rp = rpath.find( '../' )
                if ( rp != 0 ):
                    if ( rp == -1 ):
                        break
                    # a path like foo/../bar is malformed
                    raise Exception( 'absolutePath() malformed path \'%s\' ' % path )
                rpath = rpath[3:]
                wp = wpath.rfind( '/' )
                if ( wp != -1 ):
                    wpath = wpath[:wp]

            path = wdrive + wpath + '/' + rpath
        else:
            if ( rpath[0] == '/' ):
                # nothing to do: just make sure of the drive
                path = wdrive + '/' + rpath
            else:
                lp = len( path )
                if ( lp and rpath[0] == '.' ):
                    if ( 1 < lp and rpath[1] == '/' ):
                        # eliminates first './'
                        rpath = rpath[ 2:]
                    else:
                        raise Exception( 'absolutePath() malformed path \'%s\' ' % path )

                path = wdrive + wpath + '/' + rpath

        lastSep = ''
        if ( path and path[-1] == '/' ):
            lastSep = FileUtils.getNormSep( unixStyle )
        path = FileUtils.normPath( path, unixStyle ) # this eliminates the last '/' even if it is a dir
        path += lastSep

        return path
    absolutePath = staticmethod(absolutePath)

    def relativePath( basepath, path, minPathIsDot, unixStyle ):
        # the implementation currently assumes that only the basepath is a directories
        # but if the path was a directory for sure ( '/' or '\\' at the end ) then that quality is kept
        if ( not FileUtils.sameDrive( basepath, path ) ):
            raise Exception( 'relativePath() not same drive for %s and %s! ' % ( basepath, path ) )

        sep = FileUtils.getNormSep( unixStyle )

        # manages all the '../' and conform the path as in basepath
        bpath = basepath
        bpath = bpath.replace('\\', '/')
        bpath += '/'                       # (*) make sure it has '/' at the end
        bpath = bpath.replace('//', '/')   # eliminates doubles

        rpath = path
        rpath = rpath.replace('\\', '/')
        rpath = rpath.replace('//', '/')   # eliminates doubles

        ( bdrive, bpath ) = os.path.splitdrive( bpath )
        ( rdrive, rpath ) = os.path.splitdrive( rpath )

        fromRelativePath = ( rpath and rpath[0] != '/' )

        if ( fromRelativePath ):
            rp = rpath.find( '../' )
            while ( rp != -1 ):
                if ( rp != 0 ):
                    # a path like foo/../bar is malformed
                    raise Exception( 'relativePath() malformed path \'%s\' ' % path )
                else:
                    rpath = rpath[3:]
                    bp = bpath.rfind( '/' )
                    if ( bp != -1 ):
                        bpath = bpath[:bp]
                    else:
                        bpath = ''
                rp = rpath.find( '../' )
                if ( bpath == '' ):
                    raise Exception( 'relativePath() too many \'../\': the relative path cannot go up past the root of the drive. ( basepath, path ) = ( %s, %s )' % ( basepath, path ) )
                continue

            # attention: normPath eliminates all the last '/', but of course not the initial dot. It instead creates '.' if rpath was ''
            wasDirectoryForSure = ( rpath and rpath[-1] == '/' )
            rpath = FileUtils.normPath( rpath, unixStyle )
            if ( minPathIsDot ):
                if ( rpath == '.' ):
                    path = rpath + sep
                else:
                    relCurrPath = '.' + sep # '/.' or '.\\' always standing for bdrive + bpath
                    path = relCurrPath + rpath
                    if ( wasDirectoryForSure ):
                        path += sep
            else:
                if ( rpath == '.' ):
                    path = ''
                else:
                    path = rpath
                    if ( wasDirectoryForSure ):
                        path += sep
        else:
            relpath = ''
            bp = rp = 0
            if ( rp != -1 ):
                while ( bp != -1 and rp != -1 ):
                    bp = bpath.find( '/' )
                    rp = rpath.find( '/' )
                    if ( bp != -1 and rp != -1 ):
                        bs = bpath[:bp]
                        rs = rpath[:rp]
                        if ( bs.lower() == rs.lower() ):
                            bpath = bpath[bp+1:]
                            rpath = rpath[rp+1:]
                        else:
                            break

                bp = bpath.find( '/' )
                while ( bp != -1 ):
                    bp = bpath.find( '/' )
                    if ( bp != -1 ):
                        bs = bpath[:bp]
                        bpath = bpath[bp+1:]
                        relpath += '../'

                if ( minPathIsDot and relpath == '' ):
                    relpath = './'

                path = relpath + rpath

                if ( not unixStyle ):
                    path = path.replace("/", "\\")

        return path
    relativePath = staticmethod(relativePath)


################################################################################
def tck_getExtendValues( option, opt, value ):
    s = value
    return s

def getDbgRlsValues( value ):
    #transforms a string value 'd:0, r:-1' into a dictionary: { 'd': 0, 'r': -1 }
    s = value

    val = {}
    dr = s.split( ',' )
    [ d, dbg ] = dr[0].strip().split( ':' )
    [ r, rls ] = dr[1].strip().split( ':' )
    d = d.strip(); dbg = dbg.strip()
    r = r.strip(); rls = rls.strip()
    if ( d == 'd' and r == 'r' ):
        pass
    elif ( d == 'r' and r == 'd' ):
        [ d, dbg ] = dr[1].split( ':' )
        [ r, rls ] = dr[0].split( ':' )
    else:
        raise Exception( 'Bad couple of values for \'%s\'. Accepted value is: c# = d:val_dbg, r:val_rls' )

    val[d] = dbg
    val[r] = rls

    return val

def getDbgRlsValueN( value ):
    val = getDbgRlsValues( value )
    dbg = val['d']
    rls = val['r']
    val['d'] = eval(dbg)
    val['r'] = eval(rls)
    return val

def getDbgRlsValueS( value ):
    val = getDbgRlsValues( value )
    dbg = val['d']
    rls = val['r']
    dbg = StringUtils.trimCommas( dbg )
    rls = StringUtils.trimCommas( rls )
    val['d'] = dbg
    val['r'] = rls
    return val

def tck_getDbgRlsValuesN( option, opt, value ):
    val = getDbgRlsValueN( value )
    return val

def tck_getDbgRlsValuesS( option, opt, value ):
    val = getDbgRlsValueS( value )
    return val

def tck_getOptnumValues( option, opt, value ):
    val = eval( value )
    return val

class OptionEx( Option ):
    # Remark: iif the option is on the command line
    #         then Option.process () is called which essentially calls:
    #               value = self.check_value(opt, value)
    #               self.take_action(self.action, self.dest, opt, value, values, parser)

    TYPES = Option.TYPES

    TYPES = TYPES + ( "extend", )
    # --names=foo,bar --names blah --names ding,dong
    # would result in a list: ["foo", "bar", "blah", "ding", "dong"]

    TYPES = TYPES + ( "dbgrlsN", )
    # --optionPdb=d:0, r:-1
    # would result in a dictionary: { 'd': 0, 'r': -1 }

    TYPES = TYPES + ( "dbgrlsS", )
    # --optionOptimize=d:Od, r:O1
    # would result in a dictionary: { 'd': 'Od', 'r': 'O1' }

    #TYPES = TYPES + ( "optnum", )
    #ACTIONS = ACTIONS + ( "store_optnum",
    #STORE_ACTIONS = STORE_ACTIONS + ( "store_optnum", )
    #TYPED_ACTIONS = TYPED_ACTIONS + ( "store_optnum", )
    # --recurse=-r, or -r1 or -r 1
    # would equally result in options.recurse = 1
    # REMARK: to have an option like this it is necessary to subclass OptionParser._process_short_opts
    #         if we use the trick to use action="store_count" then we cannot set -v 0 because it the minimum value would be 1 (one)
    #         if we use the trick to use action="store_const" then we cannot change the value of -v from the commnad line at all


    TYPE_CHECKER = copy(Option.TYPE_CHECKER)
    TYPE_CHECKER["extend"] = tck_getExtendValues
    TYPE_CHECKER["dbgrlsN"] = tck_getDbgRlsValuesN
    TYPE_CHECKER["dbgrlsS"] = tck_getDbgRlsValuesS
    #TYPE_CHECKER["optnum"] = tck_getOptnumValues

    #ACTIONS = Option.ACTIONS + ( "store_extend", "store_dbgrls", "store_optnum" )
    #STORE_ACTIONS = Option.STORE_ACTIONS + ( "store_extend", "store_dbgrls", "store_optnum" )
    #TYPED_ACTIONS = Option.TYPED_ACTIONS + ( "store_extend", "store_dbgrls", "store_optnum" )
    ACTIONS = Option.ACTIONS + ( "store_extend", "store_dbgrlsN", "store_dbgrlsS" )
    STORE_ACTIONS = Option.STORE_ACTIONS + ( "store_extend", "store_dbgrlsN", "store_dbgrlsS" )
    TYPED_ACTIONS = Option.TYPED_ACTIONS + ( "store_extend", "store_dbgrlsN", "store_dbgrlsS" )

    def take_action (self, action, dest, opt, value, values, parser):
        if action == "store_extend":
            lvalue = value.split(",")
            values.ensure_value( dest, [] ).extend( lvalue )
        elif action == "store_dbgrlsN":
            lvalue = value
            setattr( values, dest, lvalue )
        elif action == "store_dbgrlsS":
            lvalue = value
            setattr( values, dest, lvalue )
        elif action == "store_optnum":
            lvalue = value
            if ( hasattr(values, dest) and not getattr(values, dest) is None ):
                val = getattr(values, dest)
                setattr(values, dest, val + 1)
            else:
                setattr(values, dest, values.ensure_value(dest, 0) + 1)
                # setattr( values, dest, lvalue )
            val = getattr( values, dest, 100 )
        else:
            Option.take_action(
                self, action, dest, opt, value, values, parser)

        return

    pass

################################################################################
class ExistingOptions:
    """ Collects all the options given by the user on the command line """

    def __init__ ( self, optparser, options, args=None ):
        if ( args == None ):
            args = sys.argv

        short_opt = optparser._short_opt.keys()
        long_opt = optparser._long_opt.keys()
        defaults = optparser.defaults.keys()

        self.shortOpts = {}
        self.longOpts  = {}
        self.valuesDict = {}

        self.addMembers( args, optparser, optparser._short_opt, self.shortOpts, self.valuesDict )
        self.addMembers( args, optparser, optparser._long_opt , self.longOpts, self.valuesDict  )

        #if defaults:
        #    for (attr, val) in defaults.items():
        #        setattr(self, attr, val)

        return

    def addMembers( self, args, optparser, opts, optDict, valuesDict ):
        n = 0

        optsList = opts.keys()

        for n in range( len (opts) ):
            opt = optsList[n]
            found = False

            m = opt
            if ( m and m[0] == '-' ):
                m = m[1:]
            if ( m and m[0] == '-' ):
                m = m[1:]

            lenArgs = len( args )
            for k in range( len (args) ):
                arg = args[k]
                lo = len( opt )
                la = len ( arg )
                if ( lo <= la ):
                    a = arg[:lo]
                    if ( a == opt ):
                        """
                        if ( lo <= la ):
                            option = arg[lo:]
                        else:
                            if ( k < lenArgs ):
                                option = opts[k+1]
                            else:
                                raise Exception( 'no option argument after the option %s' % opt )
                        """
                        option = opts.get( opt ) # opts is optparser._short_opt or optparser._long_opt
                        if ( option == None ):
                            raise Exception( 'no option object for option \'%s\'' % opt )
                        value = getattr( optparser.values, option.dest )
                        setattr( self, m, True )
                        optDict[ m ] = True
                        valuesDict[ m ] = value
                        found = True

            if ( not found ):
                setattr( self, m, False )
                optDict[ m ] = False
                #valuesDict[ m ] = '' # better it does not even exists ! or put the optparser.defaults in there

            continue
        return

    def getExistingOptionBetween( self, optionList ):
        exists = False
        found = False
        opt = ''
        for option in optionList:
            if ( self.shortOpts.has_key( option ) ):
                found = True
                exists = self.shortOpts[ option ]
                if ( exists ):
                    opt = option
                    break
            if ( self.longOpts.has_key( option ) ):
                found = True
                exists = self.longOpts[ option ]
                if ( exists ):
                    opt = option
                    break

        if ( not found ):
            raise Exception( 'ExistingOptions: The option \'%s\' does not exists !'% option )

        return opt

    def getExistingOptionValue( self, opt ):
        if ( self.valuesDict.has_key( opt ) ):
            value = self.valuesDict[ opt ]
        else:
            raise Exception( 'ExistingOptions: The option \'%s\' does not exists !'% opt )

        return value

class DspApp:
    def __init__(self):
        # version = '1.0.1 - 1 mar 2004'

        #self.initialCwd = self.getcwd()
        #self.workingDir = self.initialCwd
        
        self.hasOptions = False

        self.usage = "usage: %prog [-f] [-r] [-q] [-v] other args"
        self.version = "%prog - ver 1.0.0 - 13 mar 2004"
        
        self.allowedDirsList = []
        self.allowedAbsoluteDirsList = []
        self.excludedSubdirsList = []
        
        self.staticLibrariesList = []
        self.staticLibrariesListLwr = []
        self.dynamicLibrariesList = []
        self.dynamicLibrariesListLwr = []
        
        self.gtkLibrariesList = g_gtkLibrariesList # ( hardcoded )
        self.gtkLibrariesListLwr = []
        
        self.allProjectNamesList = []
        self.allProjectPathsList = []
        self.createWorkspacesList = []
        self.duplicateWorkspacesList = []
        self.allProjectNamesLwrDict = {}


        self.changedFiles   = 0
        self.unchangedFiles = 0
        self.createdFiles   = 0

        #self.configsection = ''
        optparser = OptionParser( usage=self.usage, version=self.version, option_class=OptionEx )
        optparser.add_option(   "-c", "--config"                             , type = "string"  , dest = "config"                        , default=g_default_config      , help="configuration file" )
        optparser.add_option(   "-s", "--section"                            , type = "string"  , dest = "section"                       , default=g_default_section     , help="section in the configuration file" )

        optparser.add_option(   "--workingDir"                               , type = "string"  , dest = "workingDir"                    , default='.'                   , help="set the current directory, it uses os.getCwd() if empty" )

        optparser.add_option(   "-f", "--file"                               , type = "string"  , dest = "filename"                      , default=""                    , help="process only filenames containing this string ( lettercase is ignored )" )
        optparser.add_option(   "-r", "--recurse"                            , type = "int"     , dest = "recurse"                       , default=False                 , help="recursion into subdirectories" )

        optparser.add_option(   "-v", "--verbose"                            , type = "int"     , dest = "verbose"                       , default=0                     , help="verbose level. Use -vvv to set verbose level = 3" )
        optparser.add_option(   "-w", "--warning"                            , type = "int"     , dest = "warning"                       , default=1                     , help="warning level. Use -www to set warning level = 3" )
        # optparser.add_option(   "-q", "--quiet"                              , type = "int"    , dest = "verbose"                       , default=False                 , help="reset verbose level to zero" )

        optparser.add_option(   "-p", "--prompt"                             , type = "int"     , dest = "prompt"                        , default=True                  , help="ask to press any key before continuing" )

        optparser.add_option(   "-u", "--unixStyle"                          , type = "int"     , dest = "unixStyle"                     , default=False                 , help="unix Style i.e. path with \'/\' instead than with \'\\\' " )
        optparser.add_option(   "-b", "--backupFiles"                        , type = "int"     , dest = "backupFiles"                   , default=False                 , help="not necessary ( it creates many annoying *.bak files )" )
        optparser.add_option(   "--modifyVc6"                                , type = "int"     , dest = "modifyVc6"                     , default=True                  , help="enable any modification on the original vc6 files" )

        optparser.add_option(   "--enableVcfSpecific"                        , type = "int"     , dest = "enableVcfSpecific"             , default=True                  , help="enable any vcf-specific action" )

        optparser.add_option(   "--createWorkspaces"                         , type = "int"     , dest = "createWorkspaces"              , default=True                  , help="enables creation of a workspace with all the projects we worked with ( i.e. in the allowed directories ) in it" )
        optparser.add_option(   "--duplicateWorkspaces"                      , type = "int"     , dest = "duplicateWorkspaces"           , default=True                  , help="enables duplication of a workspaces in the list in the section" )
        optparser.add_option(   "--conformLibraries"                         , type = "int"     , dest = "conformLibraries"              , default=True                  , help="conforms the libraries such that static and dynamic versions have the same body, i.e. the same groups" )

        optparser.add_option(   "--deleteSccLines"                           , type = "int"     , dest = "deleteSccLines"                , default=False                 , help="eliminates all source code control lines" )
        #optparser.add_option(   "--deleteLineString"                         , type = "string"  , dest = "deleteLineString"              , default=''                    , help="string to find for lines to be deleted ( see deleteSccLines ) ( i.e. \'# PROP Scc_\'" )
        optparser.add_option(   "--reformatOutputIntermediateDirs"           , type = "int"     , dest = "reformatOutputIntermediateDirs", default=+1                    , help="reformat the Output Directories [note though that in normal cases we want /out: and vc6 removes the /Fo option ]"        )
        optparser.add_option(   "--reformatOptionOutput"                     , type = "dbgrlsN" , dest = "reformatOptionOutput"          , default=-1                    , help="reformat the option Output                 /Fo"     )

        optparser.add_option(   "--reformatOptionOptimize"                   , type = "dbgrlsS" , dest = "reformatOptionOptimize"        , default=-1                    , help="reformat the optimization option /O# use an allowed value [ d:Od, r:O1 ] but [d:0, r:0] -> does nothing"   )
        optparser.add_option(   "--reformatOptionPdb"                        , type = "dbgrlsN" , dest = "reformatOptionPdb"             , default=-1                    , help="reformat/delete the option ProgramDatabase /pdb"    )
        optparser.add_option(   "--reformatOptionBrowse"                     , type = "dbgrlsN" , dest = "reformatOptionBrowse"          , default=-1                    , help="reformat/delete the option Browse          /Br"     )

        optparser.add_option(   "--copyToVc70"                               , type = "int"     , dest = "copyToVc70"                    , default=True                  , help="copy dsp files in corresponding directories for vc70 ( option VCF specific )" )
        optparser.add_option(   "--copyToVc71"                               , type = "int"     , dest = "copyToVc71"                    , default=True                  , help="copy dsp files in corresponding directories for vc71 ( option VCF specific )" )

        optparser.add_option(   "--allowDirs"                                , type = "int"     , dest = "allowDirs"                     , default=True                  , help="works only with selected directories and its subdirectories" )
        optparser.add_option(   "--excludeSubdirs"                           , type = "int"     , dest = "excludeSubdirs"                , default=False                 , help="exclude the subdirectories containing the strings specified in the excludeSubdirs section" )

        # Remark: unfortunately we cannot use: action = "store_const" , const = 0 for many options like -r, --recurse,
        #         otherwise the command line cannot set them to zero as they would not accept an option argument anymore: like -r 0

        args = sys.argv
        # simulates command line options
        #args = [ "-fApplicationKit.dsp", "-vvv", "-r", "0", "-u", "0", "--config", "reformatVc.ini", "-s", "deleteSccOnly" ]
        #args = [ "-r", "0", "-v", "3", "-u", "0", "--reformatOptionPdb", "d:5, r:10" ]
        ( self.options, moreargs ) = optparser.parse_args( args )
        #print self.options.filename; print self.options.config; print self.options.section;
        #print self.options.verbose;  print self.options.recurse; print self.options.reformatOptionPdb; print "";
        #print self.options.unixStyle; print optparser.print_usage()

        #if ( len(args) != 1 ):
        #    optparser.error("incorrect number of arguments")

        # I want to know which options has been given from the command line
        self.commands = ExistingOptions( optparser, self.options, args )

        self.hasOptions = True

        #import types
        self.config = ConfigParser.ConfigParser()
        self.readConfigFile()

        # make sure '/? doesn't let the program to start
        i = -1
        for s in sys.argv:
            i += 1
            if ( 0 < i and s and s[0] == '/' ):
                if ( s == '/?' or s.lower() == '/h' or s.lower() == '/help' ):
                #optparser.print_usage()
                    optparser.print_help()
                    raise Exception( 'invalid option: ' + s )

        if ( 0 < self.options.verbose ):
            self.printOptions()
            if (len (self.options.filename) ):
                print "reading %s ..." % self.options.filename

        return

    def getcwd( self ):
        # this function was introduced as a temporary workaround to a problem with Cygwin:
        #   OSError: [Errno 2] No such file or directory: '\\mntdos\\vcfcode\\devel\\vcf\\'
        # Solution: it is necessary to put options.unixStyle = True under Cygwin
        cwd = os.getcwd()
        if ( self.hasOptions ):
            cwd = FileUtils.normPathSimple( cwd, self.options.unixStyle )
        else:
            raise Exception( 'app.getcwd: no attrib options yet' )
        return cwd
    
    def printOptions( self ):
        #defaults = optparser.defaults
        #if defaults:
        #    for (attr, val) in defaults.items():
        #        #setattr(self, attr, val)
        #        x = getattr( self.options, attr )
        #        if type(x) is str:
        #            print attr + ' = ' + x
        #        if type(x) is int:
        #            print attr + ' = ' + x
        #        print attr + ' = ' + x

        print '[' + self.options.configsection + ']'
        print ' --workingDir     = ' + str(self.currentdir    )
        print ''
        print ' --config         = ' + str(self.options.config)
        print ' --section        = ' + str(self.options.section)
        print ''
        print ' --filename       = \'' + str(self.options.filename) + '\''
        print ' --recurse        = ' + str(self.options.recurse)
        print ' --verbose        = ' + str(self.options.verbose)
        print ' --warning        = ' + str(self.options.warning)
        print ' --prompt         = ' + str(self.options.prompt )
        print ''
        print ' --unixStyle      = ' + str(self.options.unixStyle)
        print ' --backupFiles    = ' + str(self.options.backupFiles)
        print ' --modifyVc6                      = ' + str(self.options.modifyVc6                       )
        print ''
        print ' --enableVcfSpecific              = ' + str(self.options.enableVcfSpecific               )
        print ' --createWorkspaces               = ' + str(self.options.createWorkspaces                )
        print ' --duplicateWorkspaces            = ' + str(self.options.duplicateWorkspaces             )
        print ' --conformLibraries               = ' + str(self.options.conformLibraries                )
        print ''
        print ' --deleteSccLines                 = ' + str(self.options.deleteSccLines                     )
        #print ' --deleteLineString               = \'' + str(self.options.deleteLineString              ) + '\''
        print ' --reformatOutputIntermediateDirs = ' + str(self.options.reformatOutputIntermediateDirs  )
        print ' --reformatOptionOutput           = ' + str(self.options.reformatOptionOutput            )

        print ''
        print ' --reformatOptionOptimize         = ' + str(self.options.reformatOptionOptimize          )
        print ' --reformatOptionPdb              = ' + str(self.options.reformatOptionPdb               )
        print ' --reformatOptionBrowse           = ' + str(self.options.reformatOptionBrowse            )

        print ' --copyToVc70                     = ' + str(self.options.copyToVc70                      )
        print ' --copyToVc71                     = ' + str(self.options.copyToVc71                      )

        print ' --allowDirs      = ' + str(self.options.allowDirs)
        if ( self.options.allowDirs ):
            print '   ' + str( self.allowedDirsList )
        print ' --excludeSubdirs = ' + str( self.options.excludeSubdirs )
        if ( self.options.excludeSubdirs ):
            print '   ' + str( self.excludedSubdirsList )
        print ''

        return

    def configGetStr( self, section, option ):
        s = self.config.get( section, option )
        s = StringUtils.stripComment( s )
        s = StringUtils.trimCommas( s )
        return s

    def configGetInt( self, section, option ):
        s = self.configGetStr( section, option )
        value = eval( s )
        return value

    def configGetBool( self, section, option ):
        s = self.configGetStr( section, option )
        return eval ( s )
        if ( False ):
            s = s.lower()
            if ( s == 'true' ):
                value = 1
            elif ( s == 'false' ):
                value = 0
            else:
                value = eval( s )

        return value

    def configGetDbgrlsN( self, section, option ):
        s = self.configGetStr( section, option )
        value = getDbgRlsValueN( s )
        return value

    def configGetDbgrlsS( self, section, option ):
        s = self.configGetStr( section, option )
        value = getDbgRlsValueS( s )
        return value

    def toBoolStr( self, val ):
        if ( val ):
            s = 'True'
        else:
            s = 'False'
        return s

    def getOptionValue( self, optionList, configSection, configOption, type ):
        # gets an option from the config file unless it has been given the option on the command line

        # example:
        #if ( self.commands.hasOption( [ 'filename', 'f' ] ) ):
        #    filename = self.commands.getOptionValue( [ 'filename', 'f' ] )
        #else:
        #    filename = self.configGetStr ( 'section_test', 'filename' )
        opt = self.commands.getExistingOptionBetween( optionList )
        if ( opt ):
            value = self.commands.getExistingOptionValue( opt )
        else:
            if ( type == 'string' ):
                value = self.configGetStr ( configSection, configOption )
            elif ( type == 'bool' ):
                value = self.configGetBool( configSection, configOption )
            elif ( type == 'dbgrlsN' ):
                value = self.configGetDbgrlsN( configSection, configOption )
            elif ( type == 'dbgrlsS' ):
                value = self.configGetDbgrlsS( configSection, configOption )
            else:
                value = self.configGetInt ( configSection, configOption )
        return value

    def readConfigFile( self ):
        # if ( self.options.config != self.configOptions.configfile )
        if ( self.options.config and os.path.exists( self.options.config ) ):
            self.config.read( self.options.config )
            if ( self.config.has_section( 'activesection' ) ):
                section = self.getOptionValue( [ 'section', 's' ], 'activesection', 'section', "string" )
                self.options.configsection = section

                if ( self.config.has_section( section ) ):
                    common_section                              = self.configGetStr ( section, 'common_section'                   )
                    # common_section is activated only if not empty name
                    if ( common_section ):
                        comm_sect = common_section
                    else:
                        comm_sect = section

                    spec_sect = section # specific section ( i.e. not the common one )

                    # common section
                    section_dirlist                             = self.configGetStr ( comm_sect, 'section_dirlist'                )
                    section_excludesubdirlist                   = self.configGetStr ( comm_sect, 'section_excludesubdirlist'      )
                    section_conformLibraries                    = self.configGetStr ( comm_sect, 'section_conformLibraries'       )
                    section_createWorkspaces                    = self.configGetStr ( comm_sect, 'section_createWorkspaces'       )
                    section_duplicateWorkspaces                 = self.configGetStr ( comm_sect, 'section_duplicateWorkspaces'    )

                    self.options.filename                       = self.getOptionValue( [ 'filename', 'f' ]                   , comm_sect, 'filename'                       , "string"    )

                    self.options.recurse                        = self.getOptionValue( [ 'recurse', 'r' ]                    , comm_sect, 'recurse'                        , "bool"      )
                    self.options.verbose                        = self.getOptionValue( [ 'verbose', 'v' ]                    , comm_sect, 'verbose'                        , "int"       )
                    self.options.warning                        = self.getOptionValue( [ 'warning', 'w' ]                    , comm_sect, 'verbose'                        , "int"       )
                    self.options.prompt                         = self.getOptionValue( [ 'prompt', 'p' ]                     , comm_sect, 'prompt'                         , "int"       )

                    self.options.unixStyle                      = self.getOptionValue( [ 'unixStyle' ]                       , comm_sect, 'unixStyle'                      , "bool"      )
                    self.options.deleteSccLines                 = self.getOptionValue( [ 'deleteSccLines' ]                  , comm_sect, 'deleteSccLines'                 , "bool"      )
                    #self.options.deleteLineString               = self.getOptionValue( [ 'deleteLineString' ]                , comm_sect, 'deleteLineString'               , "string"    )

                    self.options.reformatOutputIntermediateDirs = self.getOptionValue( [ 'reformatOutputIntermediateDirs' ]  , comm_sect, 'reformatOutputIntermediateDirs' , "int"       )
                    self.options.reformatOptionOutput           = self.getOptionValue( [ 'reformatOptionOutput' ]            , comm_sect, 'reformatOptionOutput'           , "dbgrlsN"   )

                    self.options.enableVcfSpecific              = self.getOptionValue( [ 'enableVcfSpecific' ]               , comm_sect, 'enableVcfSpecific'              , "bool"      )
                    self.options.modifyVc6                      = self.getOptionValue( [ 'modifyVc6' ]                       , comm_sect, 'modifyVc6'                      , "bool"      )

                    self.options.workingDir                     = self.getOptionValue( [ 'workingDir' ]                      , comm_sect, 'workingDir'                     , "string"    )
                    self.options.allowDirs                      = self.getOptionValue( [ 'allowDirs' ]                       , comm_sect, 'allowDirs'                      , "bool"      )
                    self.options.excludeSubdirs                 = self.getOptionValue( [ 'excludeSubdirs' ]                  , comm_sect, 'excludeSubdirs'                 , "bool"      )


                    # specific section
                    self.options.createWorkspaces               = self.getOptionValue( [ 'createWorkspaces' ]                , spec_sect, 'createWorkspaces'               , "bool"      )
                    self.options.duplicateWorkspaces            = self.getOptionValue( [ 'duplicateWorkspaces' ]             , spec_sect, 'duplicateWorkspaces'            , "bool"      )
                    self.options.conformLibraries               = self.getOptionValue( [ 'conformLibraries' ]                , spec_sect, 'conformLibraries'               , "bool"      )

                    self.options.reformatOptionOptimize         = self.getOptionValue( [ 'reformatOptionOptimize' ]          , spec_sect, 'reformatOptionOptimize'         , "dbgrlsS"   )
                    self.options.reformatOptionPdb              = self.getOptionValue( [ 'reformatOptionPdb' ]               , spec_sect, 'reformatOptionPdb'              , "dbgrlsN"   )
                    self.options.reformatOptionBrowse           = self.getOptionValue( [ 'reformatOptionBrowse' ]            , spec_sect, 'reformatOptionBrowse'           , "dbgrlsN"   )
                    self.options.copyToVc70                     = self.getOptionValue( [ 'copyToVc70' ]                      , spec_sect, 'copyToVc70'                     , "bool"      )
                    self.options.copyToVc71                     = self.getOptionValue( [ 'copyToVc71' ]                      , spec_sect, 'copyToVc71'                     , "bool"      )

                else:
                    raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section, self.options.config ) )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( 'activesection', self.options.config ) )
        else:
            raise Exception( 'The config file \'%s\' does not exists !' % self.options.config )



        if ( self.options.workingDir == '' ):
            self.currentdir = self.getcwd()
        else:
            self.currentdir = FileUtils.normDir( self.options.workingDir, True )
            if ( self.currentdir.find( './' ) != -1 ):
                self.currentdir = FileUtils.absolutePath( self.getcwd(), self.currentdir, self.options.unixStyle )

        if ( self.options.allowDirs ):
            if ( self.config.has_section( section_dirlist ) ):
                pairs = self.config.items( section_dirlist )
                self.allowedDirsList = []
                for pair in pairs:
                    ( name, namedir ) = pair
                    namedir = StringUtils.stripComment( namedir )
                    namedir = StringUtils.trimCommas( namedir )
                    namedir = namedir.lower()
                    namedir = FileUtils.normDir( namedir, self.options.unixStyle, True )
                    self.allowedDirsList.append( namedir )
                    absNamedir = FileUtils.absolutePath( self.currentdir, namedir, self.options.unixStyle )
                    self.allowedAbsoluteDirsList.append( absNamedir )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_dirlist, self.options.config ) )

        if ( self.options.excludeSubdirs ):
            if ( self.config.has_section( section_excludesubdirlist ) ):
                pairs = self.config.items( section_excludesubdirlist )
                self.excludedSubdirsList = []
                for pair in pairs:
                    ( name, namedir ) = pair
                    namedir = StringUtils.stripComment( namedir )
                    namedir = StringUtils.trimCommas( namedir )
                    namedir = namedir.lower()
                    namedir = FileUtils.normDir( namedir, self.options.unixStyle )
                    self.excludedSubdirsList.append( namedir )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_excludesubdirlist, self.options.config ) )

        if ( self.options.conformLibraries and section_conformLibraries ):
            if ( self.config.has_section( section_conformLibraries ) ):
                pairs = self.config.items( section_conformLibraries )
                self.conformLibrariesList = []
                for pair in pairs:
                    ( name, item ) = pair
                    # dllname --> nameChanged  i.e.  FoundationKit --> FoundationKitDll
                    if ( item.find( '-->' ) or item.find( '-->' ) ):
                        item = StringUtils.stripComment( item )
                        item = item.rstrip()
                        self.conformLibrariesList.append( item )
                    else:
                        raise Exception( 'Wrong format of the item \'%s = %s\' in the section \'%s\' of the config file \'%s\'\n' \
                                         'The format should be [ c# = dllname --> libname ] or [ c# = dllname <-- libname ]' % ( namesection, item, section_conformLibraries, self.options.config ) )

        section_vcf_staticLibraries = 'vcf_staticLibraries'
        ( self.staticLibrariesList, self.staticLibrariesListLwr) = self.makeLibraryDependencyList( section_vcf_staticLibraries )

        section_vcf_dynamicLibraries = 'vcf_dynamicLibraries'
        ( self.dynamicLibrariesList, self.dynamicLibrariesListLwr ) = self.makeLibraryDependencyList( section_vcf_dynamicLibraries )

        self.gtkLibrariesListLwr = []
        for name in self.gtkLibrariesList:
            self.gtkLibrariesListLwr.append( name.lower() )


        if ( self.options.createWorkspaces ):
            if ( self.config.has_section( section_createWorkspaces ) ):
                pairs = self.config.items( section_createWorkspaces )
                self.createWorkspacesList = []
                for pair in pairs:
                    ( name, workspace ) = pair
                    workspace = StringUtils.stripComment( workspace )
                    workspace = StringUtils.trimCommas( workspace )
                    # please, make sure the name contains the dirname too
                    workspace = FileUtils.relativePath( self.currentdir, workspace, True, self.options.unixStyle )
                    if ( workspace == '.' + FileUtils.getNormSep( self.options.unixStyle ) ): workspace = ''
                    # workspace = workspace.lower()
                    # workspace = FileUtils.normDir( workspace, self.options.unixStyle )
                    self.createWorkspacesList.append( workspace )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_createWorkspaces, self.options.config ) )

        if ( self.options.duplicateWorkspaces ):
            if ( self.config.has_section( section_duplicateWorkspaces ) ):
                pairs = self.config.items( section_duplicateWorkspaces )
                self.duplicateWorkspacesList = []
                for pair in pairs:
                    ( name, workspace ) = pair
                    workspace = StringUtils.stripComment( workspace )
                    workspace = StringUtils.trimCommas( workspace )
                    # please, make sure the name contains the dirname too
                    workspace = FileUtils.relativePath( self.currentdir, workspace, True, self.options.unixStyle )
                    if ( workspace == '.' + FileUtils.getNormSep( self.options.unixStyle ) ): workspace = ''
                    #workspace = workspace.lower()
                    #workspace = FileUtils.normDir( workspace, self.options.unixStyle )
                    self.duplicateWorkspacesList.append( workspace )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_duplicateWorkspaces, self.options.config ) )

        return

    def makeLibraryDependencyList( self, section ):
        libraryDependencyList = []
        libraryDependencyListLwr = []
        if ( self.config.has_section( section ) ):
            pairs = self.config.items( section )
            # the order is important ( but ConfigParser doesn't keep it ) so we need to sort
            names = []
            namesDict = {}
            for pair in pairs:
                ( name, itemStringList ) = pair
                names.append( name )
                namesDict[ name ] = itemStringList
            names.sort()

            for name in names:
                itemStringList = namesDict[ name ]
                itemStringList = StringUtils.stripComment( itemStringList )
                itemList = itemStringList.split(',')
                for item in itemList:
                    item = item.strip()
                    itemLwr = item.lower()
                    libraryDependencyList.append( item )
                    libraryDependencyListLwr.append( itemLwr )

        return ( libraryDependencyList, libraryDependencyListLwr )

    def checkAllowedDir( self, filename ):
        allow = True
        if ( app.options.allowDirs or app.options.excludeSubdirs ):
            fn = filename.lower()
            #print os.path.split( fn )
            fn = os.path.dirname( fn )
            if ( fn == '' ):
                fn = './'
            fn = FileUtils.normDir( fn, self.options.unixStyle ) # add last sep

            if ( app.options.allowDirs ):
                allow = False
                fnAbs = FileUtils.absolutePath( app.currentdir, fn, self.options.unixStyle )
                for subdir in app.allowedAbsoluteDirsList:
                    if ( fnAbs.find(subdir) != -1 ):
                        allow = True
                        break

            if ( allow and app.options.excludeSubdirs ):
                fnRel = FileUtils.relativePath( app.currentdir, fn, True, self.options.unixStyle )
                for subdir in app.excludedSubdirsList:
                    if ( fnRel.find(subdir) != -1 ):
                        allow = False
                        break

        return allow


################################################################################
class Workspace:
    """Creates a workspace with all projects in Visual Studio 6."""
    def __init__( self, workspacename ):
        self.prjNames = []
        self.absPrjPaths = []
        self.relPrjPaths = []
        self.prjNameAbsPathDict = {}
        self.prjNameRelPathDict = {}
        
        self.filename = ''
        self.setName( workspacename )
        self.dependencies = {}

    def setName( self, workspacename ):
        self.filename = workspacename
        # makes sure it has the '.dsw. extension
        ( root, ext ) = os.path.splitext( self.filename )
        if ( ext == '' ):
            self.filename = root + '.dsw'

        workspaceDirname = os.path.dirname( workspacename )
        if ( not os.path.exists( workspaceDirname ) ):
            msg = 'The directory for the workspace \'%s\' does not exist. Create it [y/n] ?' % workspacename
            c = raw_input( msg ).lower
            if ( c == 'y' or c == 'yes' ):
                os.makedirs( workspaceDirname )
            else:
                raise Exception( 'Workspace\'s directory \'%s\' not created !' % workspaceDirname )
        return

    def addProject( self, prjName, absPrjPath ):
        # prjPath must be given here as absolute path because one thing is the path relative to the cwd
        # and different thing is aa path relative to the workspace path
        self.prjNames.append( prjName )
        self.absPrjPaths.append( absPrjPath )
        self.prjNameAbsPathDict[ prjName ] = absPrjPath

        workspaceDirname = os.path.dirname( self.filename )
        relPrjPath = FileUtils.relativePath( workspaceDirname, absPrjPath, True, app.options.unixStyle )
        self.relPrjPaths.append( relPrjPath )
        self.prjNameRelPathDict[ prjName ] = relPrjPath

        return

    def duplicateVcs( self, updateOriginal ):
        if ( updateOriginal ):                # always
            self.duplicateVc( '' )  # this just reformat the original ( see duplicateVc )

        if ( app.options.copyToVc70 ):
            self.duplicateVc( compilerVc70 )

        if ( app.options.copyToVc71 ):
            self.duplicateVc( compilerVc71 )

    def duplicateVc( self, newCompiler ):
        # newCompiler == '' --> just reformat the original ( i.e. make sure projectPath has the "" around of it

        if ( app.options.enableVcfSpecific ):
            newFilename = self.filename

            # the trick to copy and rename a file is to treat it as a DspFile as far as it concerns the functions here
            wsp = DspFile( app, self.filename )
            wsp.readlines()

            wsp.removeUnwantedLines()

            Workspace.replaceProjectEntries( wsp.lines, wsp, newCompiler, self.filename )

            # newPath = DspFile.makeDuplicateVcFilename( self.filename, dsp.compiler, newCompiler, app.options.unixStyle, False )
            if ( newCompiler ):
                newFilename = wsp.getDuplicateVcFilename( newCompiler, True )
            wsp.setFilename( newFilename )

            wsp.saveFile( False )

            if ( 0 < app.options.verbose ):
                if ( newCompiler ):
                    print ' created workspace: %s' % wsp.filename
                else:
                    print ' updated workspace: %s' % wsp.filename
        return

    def replaceProjectEntries( lines, wsp, newCompiler, filename ):
        recP1 = re.compile( r'Project:\s*?"(?P<prjName>[a-zA-Z0-9_\- ]*?)"\s*?=' )
        # recP2 = re.compile( r'Project:\s*?"(?P<prjName>[a-zA-Z0-9_\- ]*?)"\s*?=\s*?"(?P<prjPath>[a-zA-Z0-9_\- \\/.]*?)"' )
        recP2 = re.compile( r'Project:\s*?"(?P<prjName>[a-zA-Z0-9_\- ]*?)"\s*?=\s*?(?P<prjPath>"?([a-zA-Z0-9_\- \\/.]*?)"?)(?P<pkgOwnr>\s*?-\s*?Package Owner)' )

        state = 0
        nPrjs = 0
        for n in range( len( lines ) ):
            line = lines[n]
            m1 = recP1.match( line )
            if ( m1 ):
                m2 = recP2.match( line )
                if ( not m2 ):
                    raise Exception( 'Bad parsing in workspace %s - line %d: %s' % ( filename, n, line ) )
                prjName = m2.group('prjName')
                prjPath = m2.group('prjPath')
                # pkgOwnr = m2.group('pkgOwnr')

                newline = r'Project: "' + prjName + r'"=' + prjPath + ' - Package Owner=<4>\n'
                if ( newline != line ):
                    print line; print newline
                    raise Exception( 'Wrong parsing in workspace %s - line[%d] [%s]  !=  newline[%s]\n [prjName = \'%s\', prjPath = \'%s\'' % ( filename, n, line, newline, prjName, prjPath ) )

                prjPath = StringUtils.trimCommas( prjPath )
                if ( newCompiler ):
                    newPath = DspFile.makeDuplicateVcFilename( prjPath, wsp.compiler, newCompiler, app.options.unixStyle, True )
                else:
                    # we need to do this first otherwise problems under Cygwin when unixStyle=True but the path starts with r'.\'
                    newPath = FileUtils.normPathSimple( prjPath, app.options.unixStyle )
                    
                newline = r'Project: "' + prjName + r'"="' + newPath + '" - Package Owner=<4>\n'

                lines[n] = newline

            pass
        return lines
    replaceProjectEntries = staticmethod(replaceProjectEntries)

    def fillProjectsLists( self, filterString, ignorecase, addLibraries=False, addGtkLibraries=False ):
        self.prjNames = []
        self.absPrjPaths = []
        self.relPrjPaths = []
        self.prjNameAbsPathDict = {}
        self.prjNameRelPathDict = {}
        
        #filterStringLwr = filterString.lower()
        #filterStringDir = os.path.dirname( filterStringLwr )
        #filterStringDir = FileUtils.normDir( filterStringDir, app.options.unixStyle, True )
        #filterString = filterStringDir
        filterString = FileUtils.normPathSimple( filterString, app.options.unixStyle )
        if ( ignorecase ):
            filterString = filterString.lower()

        for n in range( len( app.allProjectPathsList )):
            prjName    = app.allProjectNamesList[n]
            absPrjPath = app.allProjectPathsList[n]
            relPrjPath = FileUtils.relativePath( app.currentdir, absPrjPath, True, app.options.unixStyle )
            relPrjPathLwr = relPrjPath
            if ( ignorecase ):
                relPrjPathLwr = relPrjPathLwr.lower()                    
            if ( not filterString or relPrjPathLwr.find( filterString ) != -1 ):
                # do not use FileUtils.relativePath because one thing is the path relative to the cwd and different thing is a path relative to the workspace path
                self.addProject( prjName, absPrjPath )
                
        return

    def fillProjectsListsAddLibraries( self, filteredList ):
        if ( filteredList ):
            # filter: we need to add the libraries
            addLibrariesStatic  = True
            addLibrariesDynamic = True
            #JC I turned this to False so that we don't bother with GTK Libs
            addLibrariesGtk     = False
            
            if ( addLibrariesStatic ):
                for prjName in app.staticLibrariesList:
                    if ( not app.prjNameAbsPathDict.has_key( prjName ) ):
                        raise Exception ( 'fillProjectsListsAddLibraries: please use the right lettercase for the library list \'%s\'' % prjName )
                    absPrjPath = app.prjNameAbsPathDict[ prjName ]
                    self.addProject( prjName, absPrjPath )

            if ( addLibrariesDynamic ):
                for prjName in app.dynamicLibrariesList:
                    absPrjPath = app.prjNameAbsPathDict[ prjName ]
                    self.addProject( prjName, absPrjPath )
                    
            if ( addLibrariesGtk ):
                for prjName in app.gtkLibrariesList:
                    absPrjPath = app.prjNameAbsPathDict[ prjName ]
                    self.addProject( prjName, absPrjPath )
        else:
            # no filter: all projects are in
            app.prjNameAbsPathDict = self.prjNameAbsPathDict
        return

    def create( self, projNamesList, projPathsList, filterString, ignorecase ):
        # ???
        #if ( not app.options.conformLibraries ):
        #    return

        self.fillProjectsLists( filterString, ignorecase )
        
        filteredList = ( filterString and filterString != '.' and filterString != './' and filterString != '.\\' )
        self.fillProjectsListsAddLibraries( filteredList )
        
        self.copyWorkspaceDependencies( g_dependenciesWorkspace )

        workspacedirname = os.path.dirname( self.filename )
        if ( not os.path.exists( workspacedirname ) ):
            raise Exception( 'Workspace directory \'%s\' does not exist.\n           It should have been already created !' % workspacedirname )

        if ( os.path.exists( self.filename ) ):
            os.remove( self.filename )

        fd = file( self.filename, 'w' );

        header =  'Microsoft Developer Studio Workspace File, Format Version 6.00\n'
        header += '# WARNING: DO NOT EDIT OR DELETE THIS WORKSPACE FILE!\n'
        header += '\n'
        header += '###############################################################################\n'
        header += '\n'
        fd.writelines( header )


        #'Project: "%s"="%s" - Package Owner=<4>\n'
        prjBody1 =  '\n'
        prjBody1 += 'Package=<5>\n'
        prjBody1 += '{{{\n'
        prjBody1 += '}}}\n'
        prjBody1 += '\n'
        prjBody1 += 'Package=<4>\n'
        prjBody1 += '{{{\n'
        #'    Begin Project Dependency'
        #'    Project_Dep_Name Dialogs'
        #'    End Project Dependency'
        prjBody2 =  '}}}\n'
        prjBody2 += '\n'
        prjBody2 += '###############################################################################\n'
        prjBody2 += '\n'

        #sorting ( this is one way ... )
        #projects = zip( self.prjNames, self.relPrjPaths )
        #projects.sort()
        # for (prjName, relPrjPath) in projects:

        #sorting ( ... and this is another way )
        prjNames = self.prjNames
        # unfortunatly lowercase name goes after so...
        # prjNames.sort()
        prjNamesLwr = []
        for name in prjNames:
            prjNamesLwr.append( name.lower() )
        prjNamesLwr.sort()

        dependencyStringList = ''
        for prjNameLwr in prjNamesLwr:
            prjName = app.allProjectNamesLwrDict[ prjNameLwr ]
            relPrjPath = self.prjNameRelPathDict[ prjName ]

            prjLine = r'Project: "' + prjName + r'"="' + relPrjPath + '" - Package Owner=<4>\n'
            fd.writelines( prjLine )

            fd.writelines( prjBody1 )

            # some projects need all the necessary dependencies ( hardcoded )
            if ( prjName.lower() == 'examples' ): # e.g. 'examples'
                dependencyStringListLib = self.buildDependencyStringListItem( 'ApplicationKitDLL' )
                dependencyStringAllProjects = self.calcDependencyStringListAllProjects( prjName, prjNames, g_dependencyFilterExamplesProject )
                dependencyStringList = dependencyStringListLib + dependencyStringAllProjects
            else:
                dependencyStringList = self.calcDependencyStringList( prjName )
                if ( not dependencyStringList ):
                    # for projects without dependencies, copies them from g_dependenciesWorkspace
                    if ( self.dependencies ):
                        if ( self.dependencies.has_key( prjName ) ):
                            dependencyStringList = self.dependencies[ prjName ]
                    

            if ( dependencyStringList ):
                fd.writelines( dependencyStringList )

            fd.writelines( prjBody2 )

        fd.close

        print ' created workspace: %s' % self.filename

        return

    def copyWorkspaceDependencies( self, dependencyWorkspaceName ):
        self.dependencies.clear()

        if ( not dependencyWorkspaceName ):
            return

        dependencyWorkspaceDirname = os.path.dirname( dependencyWorkspaceName )
        if ( not os.path.exists( dependencyWorkspaceDirname ) ):
            raise Exception( 'Dependency Workspace directory \'%s\' does not exist !\n' % dependencyWorkspaceDirname )
        if ( not os.path.exists( dependencyWorkspaceName ) ):
            raise Exception( 'Dependency Workspace \'%s\' does not exist !\n' % dependencyWorkspaceName )

        fw = file( dependencyWorkspaceName, 'r' );
        wlines = fw.readlines()
        fw.close

        rec = re.compile( r'Project:\s*?"(?P<prjName>[a-zA-Z0-9_\- ]*?)"\s*?=' )

        dependencyStringList = ''
        state = 0
        nPrjs = 0
        for n in range( len( wlines ) ):
            line = wlines[n]

            if ( state == 0 ):
                dependencyStringList = ''
                m = rec.match( line )
                if ( m ):
                    prjName = m.group('prjName')
                    if ( not prjName ):
                        raise Exception( 'Error: no project extracted from line [%d]: %s' % ( n, line ) )
                    nPrjs += 1
                    state = 1
            elif ( state == 1 and re.match( 'Package=<4>', line ) ):
                state = 2
            elif ( state == 2 and re.match( '{{{', line ) ):
                state = 3
            elif ( state == 3 ):
                if ( re.match( '}}}', line ) ):
                    self.dependencies[ prjName ] = dependencyStringList
                    state = 0
                else:
                    dependencyStringList += line
            else:
                pass

        nDeps = len( self.dependencies )
        if ( nDeps != nPrjs ):
            raise Exception( 'dependencies[%d] != nPrjs[%d] ( state[%d] ). Workspace: %s' % ( nDeps, nPrjs, state, dependencyWorkspaceName ) )
        elif ( state != 0 ):
            raise Exception( 'wrong state: [%d]  ( but dependencies[%d] == nPrjs[%d] ). Workspace: %s' % ( state, nDeps, nPrjs, dependencyWorkspaceName ) )

        return

    def calcDependencyStringListAllProjects( self, projectName, prjNames, filterString ):
        # for a generic projectName it calculates all its dependencies and puts them in string
        dependencyStringAllProjects = ''
        projectNameLwr = projectName.lower()
        filterString = filterString.lower()
        for prjName in prjNames:
            # path relative to this workspace
            relPrjPath = self.prjNameRelPathDict[ prjName ]
            # path relative to app.currentdir
            absPrjPath = self.prjNameAbsPathDict[ prjName ]
            relPrjPath = FileUtils.relativePath( app.currentdir, absPrjPath, True, app.options.unixStyle )
            relPrjPath = relPrjPath.lower()
            relPrjPath = relPrjPath.replace("\\", "/")
            if ( relPrjPath.find( filterString ) != -1 ):
                if ( prjName.lower() != projectNameLwr ):
                    dependencyStringAllProjects += self.buildDependencyStringListItem( prjName )
        return dependencyStringAllProjects

    def calcDependencyStringList( self, project ):
        # calc the dependency string of the library that a library project is dependent of
        # this string generally consists of the only library project that must be compiled before the library project itself
        lib = ''
        dependencyStringList = ''
        libDependList = []
        libDependListLwr = []
        if ( not libDependList ):
            ( libDependList, libDependListLwr ) = self.calcLibraryDependencyList( project, app.staticLibrariesList, app.staticLibrariesListLwr )
            if ( libDependList ):
                lib = libDependList[-1]
        if ( not libDependList ):
            ( libDependList, libDependListLwr ) = self.calcLibraryDependencyList( project, app.dynamicLibrariesList, app.dynamicLibrariesListLwr )
            if ( libDependList ):
                lib = libDependList[-1]
        if ( not libDependList ):
            ( libDependList, libDependListLwr ) = self.calcLibraryDependencyList( project, app.gtkLibrariesList, app.gtkLibrariesListLwr )
            if ( libDependList ):
                lib = libDependList[-1]

        # because of a bug(?) in Visual Studio, it is necessary to put only the highest project in the dependency list
        #for lib in libraryDependencyList:
        #    dependencyStringList += self.buildDependencyStringListItem( lib )
        if lib:
            dependencyStringList += self.buildDependencyStringListItem( lib )

        return dependencyStringList

    def calcLibraryDependencyList( self, project, libraryList, libraryListLwr ):
        # calc the list of all libraries that the library project is dependent of
        # it gives both the normalcase and lowercase version of it
        libraryDependencyList = []
        libraryDependencyListLwr = []
        project = project.lower()

        if ( project in libraryListLwr ):
            for n in range ( len( libraryList ) ):
                lib = libraryList[n]
                libLwr = lib.lower()
                if ( lib.lower() == project ):
                    break
                libraryDependencyList.append( lib )
                libraryDependencyListLwr.append( libLwr )

        return ( libraryDependencyList, libraryDependencyListLwr )

    def buildDependencyStringListItem( self, project ):
        # build the dependency string of a project to be used in a workspace
        dependencyStringListItem = ''
        dependencyStringListItem += '    Begin Project Dependency\n'
        dependencyStringListItem += '    Project_Dep_Name ' + project + '\n'
        dependencyStringListItem += '    End Project Dependency\n'
        return dependencyStringListItem

    def conformAllLibraries( self ):
        if ( not app.options.conformLibraries ):
            return

        # we need to have this table filled with all the vcf projects
        self.fillProjectsLists( './', False )

        tableAssocDllsLibs = {}
        #tableAssocDllsLibs = [ ( 'FoundationKitDLL'  , 'FoundationKit'             ), \
        #                       ( 'GraphicsKitDLL'    , 'GraphicsKit'               ), \
        #                       ( 'ApplicationKitDLL' , 'ApplicationKit'            ), \
        #                       ( 'NetworkKitDLL'     , 'NetworkKit'                ), \
        #                       ( 'RemoteObjectKit'   , 'RemoteObjectKitStatic'     ), \
        #                       ( 'Win32HTMLBrowser'  , 'Win32HTMLBrowser_StaticLib')  ]

        for item in app.conformLibrariesList:
            # dllname --> libname or dllname --> libname
            lp = len( '-->' )
            p = item.find( '-->' )
            if ( p != -1 ):
                masterIsLeft = True
            else:
                p = item.find( '<--' )
                if ( p != -1 ):
                    masterIsLeft = False

            if ( p != -1 ):
                if ( masterIsLeft ):
                    nameMaster = item[:p]
                    nameChanged = item[p+lp:]
                else:
                    nameChanged = item[:p]
                    nameMaster  = item[p+lp:]

                nameMaster = StringUtils.trimCommas( nameMaster )
                nameMaster = nameMaster.strip()

                nameChanged = StringUtils.trimCommas( nameChanged )
                nameChanged = nameChanged.strip()

                tableAssocDllsLibs[ nameChanged ] = nameMaster
            else:
                raise Exception( 'Wrong format of the item \'%s = %s\'. See the config file \'%s\'\n' \
                                 'The format should be [ c# = dllname --> libname ] or [ c# = dllname <-- libname ]' % ( namesection, item, self.options.config ) )


        # sort ( it's nicer )
        prjNames = self.prjNames
        prjNames.sort()

        nc = 0
        libsc = []
        for prjName in self.prjNames:
            if ( tableAssocDllsLibs.has_key( prjName ) ):
                nameChanged = prjName
                nameMaster = tableAssocDllsLibs[ nameChanged ]

                absPathChanged = self.prjNameAbsPathDict[ nameChanged ]
                absPathMaster  = self.prjNameAbsPathDict[ nameMaster  ]

                self.conformLibrary( absPathMaster, absPathChanged )
                libsc.append( nameChanged )
                nc += 1

        if ( nc == len( tableAssocDllsLibs ) ):
            print ' %d libraries conformed  ' % nc # + str( libsc )
        else:
            ncNotFound = len( tableAssocDllsLibs ) - nc
            print ' %d libraries conformed  *** but %d librares not found ! ***' % ( nc, ncNotFound )

        return

    def conformLibrary( self, filenameMaster, filenameChanged ):
        dr = DspFile( app, filenameMaster )
        dr.readlines()
        targetSection = dr.readTargetSection()

        dw = DspFile( app, filenameChanged )
        dw.readlines()
        configurationSection = dw.readConfigurationSection()

        tmpFilename = dw.replaceAllSections( configurationSection, targetSection )

        dw.replaceWithFile( tmpFilename, False )

        nameMaster  = os.path.basename ( filenameMaster )
        nameChanged = os.path.basename ( filenameChanged )
        print ' conformed library [ %-30s --> %-30s ]' % ( nameMaster, nameChanged )

        return


################################################################################
class DspFile:
    """Process and reformat dsp files as in Visual Studio 6."""

    def __init__( self, app, filename ):

        self.app = app
        self.filename  = ''
        self.filetitle = ''
        self.setFilename( filename )

        self.compiler          = ''
        self.compilerUnderscor = ''
        self.compilerSep       = ''
        self.setCompilerStrings( compilerVc6 )

        self.lines = []
        self.n = 0
        self.storedOptions = []
        self.lastRegexGroupFound = '' # for debug only

        self.isDebugCfg  = []
        self.c  = '' # flag ='d' for debug configuration ='r' for release configuration
        self.isStaticCfg = []

        self.PropOutputDirList  = []    # directory for output
        self.PropIntermeDirList = []    # directory for intermediate output
        self.OutputDirOutList   = []    # directory for main output ( it is usually the same as PropOutputDirList, but sometimes we want to /out: somewhereelse )
        self.MainFileTitleBase = ''
        self.outputExt = ''

        self.PropOutputDir  = ''
        self.PropIntermeDir = ''
        self.OutputDirOut   = ''

        self.appType = enumAppTypeNone

        self.trueProjectName = ''
        self.projectName = ''
        self.configName = ''
        self.addKind = enum_ADD_NONE
        
        self.resetWarnings()

        return

    def reset( self ):
        self.lines = []
        self.n = 0
        self.storedOptions = []
        self.lastRegexGroupFound = '' # for debug only

        self.isDebugCfg  = []
        self.c = ''
        self.isStaticCfg = []

        self.PropOutputDirList  = []    # directory for output
        self.PropIntermeDirList = []    # directory for intermediate output
        self.OutputDirOutList   = []    # directory for main output ( it is usually the same as PropOutputDirList, but sometimes we want to /out: somewhereelse )
        self.MainFileTitleBase = ''
        self.outputExt = ''

        self.PropOutputDir  = ''
        self.PropIntermeDir = ''
        self.OutputDirOut   = ''

        self.appType = enumAppTypeNone

        self.trueProjectName = ''
        self.projectName = ''
        self.configName = ''
        self.addKind = enum_ADD_NONE
        
        self.resetWarnings()
        
        return

    def resetWarnings( self ):
        self.wdone_dirs_different = False
        return
    
    def setFilename( self, filename ):
        self.filename = filename
        self.filetitle = os.path.basename( filename )
        return

    def setTrueProjectName( self, trueProjectName ):
        self.trueProjectName = trueProjectName
        return

    def getTrueProjectName( self ):
        return self.trueProjectName

    def makeCompilerStrings( compiler, unixStyle ):
        compiler          = compiler
        compilerUnderscor = '_' + compiler
        compilerSep       = compiler + FileUtils.getNormSep( unixStyle )
        return ( compiler, compilerUnderscor, compilerSep )
    makeCompilerStrings = staticmethod(makeCompilerStrings)

    def setCompilerStrings( self, compiler ):
        ( self.compiler, self.compilerUnderscor, self.compilerSep ) = DspFile.makeCompilerStrings( compiler, app.options.unixStyle )
        return

    def getCompilerStrings( self ):
        compilerStrings = ( self.compiler, self.compilerUnderscor, self.compilerSep )
        return compilerStrings

    def getDuplicateVcFilename( self, newCompiler, keepFirstDot ):
        return DspFile.makeDuplicateVcFilename( self.filename, self.compiler, newCompiler, app.options.unixStyle, keepFirstDot )

    def makeDuplicateVcFilename( filename, oldCompiler, newCompiler, unixStyle, keepFirstDot ):
        # if the filename is under a ocplUnderscor/ subdirectory then it is copied into a ncplUnderscor/ subdirectory
        # otherwise is copied into a ncplUnderscor file in the same directory

        ( ocpl, ocplUnderscor, ocplSep ) = DspFile.makeCompilerStrings( oldCompiler, unixStyle )
        ( ncpl, ncplUnderscor, ncplSep ) = DspFile.makeCompilerStrings( newCompiler, unixStyle )

        filename = FileUtils.normPath( filename, unixStyle, keepFirstDot )
        fn = filename.lower()

        sep = FileUtils.getNormSep( unixStyle )
        ocs = ocplSep.lower()

        if ( app.options.enableVcfSpecific ):
            if ( ocpl == compilerVc6 ):
                # the directory is vc60 instead then vc6
                ocs = ocpl.lower() + '0' + sep

        i = fn.find( ocs )
        if ( i != -1 ):
            # copied into a ncpl/ subdirectory
            locs = len( ocs )
            filename = filename[:i] + ncplSep + filename[i+locs:]

            fn = os.path.dirname( filename )
            if ( not os.path.exists(fn) ):
                os.makedirs( fn )

        if ( True ): # else
            # copied into a _ncpl file in the same directory
            ( basename, ext ) = os.path.splitext( filename )
            bn = basename.lower()
            su = ncplUnderscor.lower()
            i = bn.find( su )
            if ( i != -1 ):
                lsu = len( su )
                basename = basename[:i] + ncplUnderscor + basename[i+lsu:]
                filename = basename + ext
            else:
                filename = basename + ncplUnderscor + ext

        return filename
    makeDuplicateVcFilename = staticmethod(makeDuplicateVcFilename)

    def duplicateVcs( self ):
        if ( app.options.copyToVc70 ):
            self.duplicateVc( compilerVc70 )

        if ( app.options.copyToVc71 ):
            self.duplicateVc( compilerVc71 )

    def duplicateVc( self, newCompiler ):
        if ( app.options.enableVcfSpecific ):
            dsp = DspFile( app, self.filename )
            dsp.readlines()

            newFilename = dsp.getDuplicateVcFilename( newCompiler, True )
            dsp.setFilename( newFilename )

            dsp.replaceCompilerConfig( newCompiler, True )

            dsp.saveFile( False )
            if ( 1 < app.options.verbose ):
                # we require 1 verbose level more if we modifyVc6
                if ( not app.options.modifyVc6 or 2 < app.options.verbose ):
                    basename = os.path.basename( self.filename )
                    print ' duplicated [ %s  -> %s ]' % ( basename, newFilename )
        return

    def reformat( self ):
        self.readlines()
        self.process()
        if ( app.options.modifyVc6 ):
            self.saveFile( True )
        return

    def readlines(self):
        fs = file( self.filename, 'r' );

        # Get the new lines
        self.lines = fs.readlines()
        fs.close

    def saveFile( self, count ):
        return self.saveFileContentAs( self.filename, count )

    def saveFileContentAs( self, destination, count ):
        tmpFilename = destination + '.$x$y$'
        #print 'tmpFilename ' + tmpFilename
        if ( os.path.exists( tmpFilename ) ) :
            os.remove( tmpFilename );

        fd = file( tmpFilename, 'w' );
        fd.writelines( self.lines )
        fd.close()

        if ( not os.path.exists( tmpFilename ) ) :
            raise Exception( 'saveFile() - the temporary file \'%s\' had not been created !' % source )

        self.replaceWithFile( tmpFilename, count )

        return

    def replaceWithFile( self, source, count ):
        destination = self.filename

        ( changedFiles, unchangedFiles, createdFiles ) \
                    = FileUtils.replaceFile( source, destination )
        if ( count ):
            app.changedFiles   += changedFiles
            app.unchangedFiles += unchangedFiles
            app.createdFiles   += createdFiles

        return

    def replaceCompilerConfig( self, newCompiler, onlyInsideConfig ):
        # replaces the entries oldcompiler --> newcompiler only inside the configurations section of a dsp file
        insideCfg = False
        self.nCfg = -1

        insideCfg = False
        if ( not onlyInsideConfig ):
            insideCfg = True

        ( ocpl, ocplUnderscor, ocplSep ) = DspFile.makeCompilerStrings( self.compiler, app.options.unixStyle )
        ( ncpl, ncplUnderscor, ncplSep ) = DspFile.makeCompilerStrings( newCompiler  , app.options.unixStyle )

        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n

            #* exit after end of CFG section
            if ( line.find( '# Begin Target' ) != -1 ):
                insideCfg = False
                break

            if ( onlyInsideConfig ):
                if ( line[0] == '!' ):
                    m = re_configuration.search( line )
                    if ( m ):
                        insideCfg = True

            if ( insideCfg ):
                changed = False
                i = 0
                while ( i != -1 ):
                    i = line.find( ocplUnderscor )
                    if ( i != -1 ):
                        ocplUnderscorLen = len( ocplUnderscor )
                        line = line[:i] + ncplUnderscor + line[i+ocplUnderscorLen:]
                        changed = True
                i = 0
                while ( i != -1 ):
                    i = line.find( ocplSep )
                    if ( i != -1 ):
                        ocplSepLen = len( ocplSep )
                        line = line[:i] + ncplSep + line[i+ocplSepLen:]
                        changed = True

                if ( changed ):
                    self.lines[n] = line # apply changes

        return

    def readTargetSection( self ):
        # skips all the configuration lines and copy all the target body into a string

        targetSection = ''
        state = 0
        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n

            # skips the configurations body
            if ( state == 0 and re.match( '# Begin Target', line ) ):
                state = 1

            elif ( state == 1 and re.match( '# Begin Group', line ) ):
                targetSection += line
                state = 2

            elif ( state == 2 ):
                targetSection += line
                if ( re.match( '# End Project', line ) ):
                    state = 3

            else:
                pass

        if ( state != 3 ):
            raise Exception( 'wrong final state: [%d]. Read %d lines in \'%s\'' % ( state, self.n, self.filename ) )

        return targetSection

    def readConfigurationSection( self ):
        # read all the configuration lines and copy them all into a string

        configurationSection = ''
        state = 0
        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n

            # skips the configurations body
            if ( state == 0 ):
                configurationSection += line
                if ( re.match( '# Begin Target', line ) ):
                    state = 1

            elif ( state == 1 ):
                # the part with the application names is still very specific of this project so we copy this one part too
                if ( re.match( '# Begin Group', line ) ):
                    state = 2
                    break
                else:
                    configurationSection += line

            else:
                pass

        if ( state != 2 ):
            raise Exception( 'wrong final state: [%d]. Read %d lines in \'%s\'' % ( state, self.n, self.filename ) )

        return ( configurationSection )

    def replaceAllSections( self, configurationSection, targetSection ):
        tmpFilename = self.filename + '.$x$y$'

        #print 'tmpFilename ' + tmpFilename
        if ( os.path.exists( tmpFilename ) ) :
            os.remove( tmpFilename );

        fd = file( tmpFilename, 'w' );
        fd.writelines( configurationSection )
        fd.writelines( targetSection )
        fd.close()

        if ( not os.path.exists( tmpFilename ) ) :
            raise Exception( 'replaceTarget() - the temporary file \'%s\' had not been created !' % tmpFilename )

        return tmpFilename

    def process(self):
        self.removeUnwantedLines()

        self.getOutputTypeAndDir()
        self.modifyLines()

    def removeUnwantedLines( self ):
        if ( app.options.deleteSccLines ):
            self.removeSccLines()

    def removeSccLines( self ):
        self.removeLines( '# PROP Scc_', False, '', True, True )
        self.removeLines( 'begin source code control', False, 'end source code control', True, True )
        return

    def removeLines( self, contentFirst, ignorecase, contentLast, included, trimmed ):
        # remove lines containing contentFirst,
        # or in between those containing contentFirst - contentLast
        if ( app.options.deleteSccLines ):
            inside = False
            deleteRangeLines = ( 0 < len( contentLast ))

            if ( ignorecase ):
                content = content.lower()
                contentLast = contentLast.lower()

            # reverse loop
            for i in range( len(self.lines)-1, -1, -1 ):
                line = self.lines[i]
                if ( ignorecase ):
                    line = line.lower()
                if ( trimmed ):
                    line = line.strip()
                    line += '\n' # because strip eliminates it

                delete = False
                if ( deleteRangeLines ):
                    if ( inside ):
                        if ( line.find( contentFirst ) == 0 ):
                            if ( included ):
                                delete = True
                            inside = False
                        else:
                            delete = True
                    else:
                        if ( line.find( contentLast ) == 0 ):
                            if ( included ):
                                delete = True
                            inside = True
                else:
                    if ( line.find( contentFirst ) == 0 ):
                        delete = True

                if ( delete ):
                    self.lines[i:i+1] = []  # removes line i

                continue
        return


    def checkSetDebug( self ):
        # this is a naive way to understand if a configuration is debug or not
        # ( just by the name given by the user to the configuaration itself )
        # It should be much better to check for a /D "_DEBUG"or /D "NDEBUG" macro in the CPP line
        configName  = self.configName.lower()
        self.isDebugCfg .append( configName.find( 'debug'  ) != -1 )
        if ( configName.find( 'debug' ) != -1 ):
            self.c = 'd'
        else:
            self.c = 'r'
        return

    def getOutputTypeAndDir( self ):
        insideCfg = False
        self.nCfg = -1
        self.projecName = ''
        self.configName = ''

        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n

            #* exit after end of CFG section
            if ( line.find( '# Begin Target' ) != -1 ):
                insideCfg = False
                break

            if ( self.n < 3 ):
                m = re_trueproject.match( line )
                if ( m ):
                    self.trueProjectName = m.group('trueProjectName')
                    self.setTrueProjectName( self.trueProjectName )
                    continue

            #!IF  "$(CFG)" == "ApplicationKit - Win32 Release"
            if ( line[0] == '!' ) :
                m = re_configuration.search( line )
                if ( m ):
                    insideCfg = True
                    self.nCfg += 1
                    self.OutputDirOutList  .append( '')
                    self.PropOutputDirList .append( '')
                    self.PropIntermeDirList.append( '')
                    self.projectName = m.group('projectName')
                    self.platform    = m.group('platform').rstrip() # we don't really need it
                    self.configName  = m.group('configName')
                    continue

            #* Modify 'PROP Intermediate_Dir "vc6/ReleaseDLL\obj"' and set intermediateDir
            if ( 0 <= self.nCfg ):
                #if ( self.appType == enumAppTypeNone ):
                #isStaticlib = False
                if ( re_PROP.search( line ) ):
                    if ( re_output_or_intermed_dir.match( line ) ):
                        #* Fix bug 'Debug' word in 'Release' CFG:
                        if ( self.configName == 'Release' ) :
                            line = line.replace( 'Debug', 'Release' )
                            self.lines[n] = line

                        self.extractOutputIntermDir( line )
                        continue

                elif ( re_ADD.search( line ) ):
                    # try for dll or exe
                    if ( re_ADD_LINK32.match( line ) ):
                        if ( line.find( r'/dll' ) != -1 ):
                            self.appType = enumAppTypeDll
                            self.outputExt = '.dll'
                        self.extractMainOutDir( line )
                        continue

                    # try for lib
                    elif ( re_ADD_LIB32.match( line ) ):
                        #isStaticlib = True
                        self.appType = enumAppTypeLib
                        self.outputExt = '.lib'
                        self.extractMainOutDir( line )
                        continue

                #if ( re_LIB32_static.match( line ) ):
                #    self.appType = enumAppTypeLib
                #    self.outputExt = '.lib'
                #    isStaticlib = True
                #    continue


        pass # end for

        if ( self.appType == enumAppTypeNone ):
            self.appType = enumAppTypeExe
            self.outputExt = '.exe'

        return

    def modifyLines( self ):
        self.nCfg = -1
        insideCfg = False
        self.isDebugCfg  = []
        self.c = ''
        self.isStaticCfg = []
        self.projecName = ''
        self.configName = ''

        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n

            if ( line.find( '# Begin Target' ) != -1 ):
                insideCfg = False
                break

            #!IF  "$(CFG)" == "ApplicationKit - Win32 Release"
            if ( line[0] == '!' ):
                m = re_configuration.search( line )
                if ( m ):
                    insideCfg = True
                    self.nCfg += 1
                    self.projectName = m.group('projectName')
                    self.platform    = m.group('platform').rstrip() # we don't really need it
                    self.configName  = m.group('configName')

                    self.checkSetDebug()
                    configName  = self.configName.lower()
                    self.isStaticCfg.append( configName.find( 'static' ) != -1 ) # unused

                    #if ( self.MainFileTitleBase != '' ):
                    #    fileTitle = self.MainFileTitleBase
                    #else:
                    #    fileTitle = projectName

                    self.PropOutputDir  = self.PropOutputDirList [self.nCfg]
                    self.PropIntermeDir = self.PropIntermeDirList[self.nCfg]
                    self.OutputDirOut   = self.OutputDirOutList  [self.nCfg]
                    #mainCurrOutpDir = self.MainCurrOutpDir
                    continue

            #* Modify 'PROP Intermediate_Dir "vc6/ReleaseDLL\obj"' and set intermediateDir
            if ( 0 <= self.nCfg ):
                changed = False
                if ( re_PROP.search( line ) ):
                    if ( app.options.reformatOutputIntermediateDirs == 1 ):
                        m = re_output_or_intermed_dir.match( line )
                        if ( m ):
                            subdir = m.group('subdir')
                            line = self.addReformatOutputIntermediateDirs( line, subdir )
                            changed = True

                else:
                    if ( re_ADD_CPP.match( line ) ):
                        self.addKind = enum_ADD_CPP
                        line = self.changeOptionsCpp( line )
                        changed = True

                    elif ( re_SUBTRACT_CPP.match( line ) ):
                        self.addKind = enum_SUBTRACT_CPP
                        line = self.changeOptionsCpp( line )
                        changed = True

                    elif ( re_ADD_LINK32.match( line ) ):
                        self.addKind = enum_ADD_LINK32
                        line = self.changeOptionsLnk( line )
                        changed = True

                    elif ( re_SUBTRACT_LINK32.match( line ) ):
                        self.addKind = enum_SUBTRACT_LINK32
                        line = self.changeOptionsLnk( line )
                        changed = True

                    elif ( re_ADD_LIB32.match( line ) ):
                        self.addKind = enum_ADD_LIB32
                        line = self.changeOptionsLib( line )
                        changed = True

                    elif ( re_SUBTRACT_LIB32.match( line ) ):
                        self.addKind = enum_SUBTRACT_LIB32
                        line = self.changeOptionsLib( line )
                        changed = True

                    elif ( re_ADD_BSC32.match( line ) ):
                        self.addKind = enum_ADD_BSC32
                        line = self.changeOptionsBsc( line )
                        changed = True

                if ( changed ):
                    line = StringUtils.stripSpacesInExcess( line )
                    self.lines[n] = line
        return

    def getPostFixIndex( self, filename ):
        basetitle = filename
        i = basetitle.rfind( '_' )
        if ( i != -1 ):
            name = basetitle[:i]
            postfix = basetitle[i+1:]
            if ( postfix == 'd' or postfix == 's' or postfix == 'sd' or postfix == compilerVc6 ):
                basetitle = name
                #j = filename.rfind( '_', i-1 )  # the start index specification DOESN'T WORK AT ALL
                j = basetitle.rfind( '_' )
                if ( j != -1 ):
                    name = basetitle[:j]
                    postfix = filename[j+1:i]
                    if ( postfix == compilerVc6 ):
                        basetitle = name
                    else:
                        j = i
                i = j
            else:
                i = len( basetitle )
        return ( i, basetitle )

    def getPostFix( self ):
        postfix = '_' + compilerVc6
        if ( self.appType == enumAppTypeDll ):
            if ( self.isDebugCfg[self.nCfg] ):
                postfix += '_d'
        elif ( self.appType == enumAppTypeLib ):
            if ( self.isDebugCfg[self.nCfg] ):
                postfix += '_sd'
            else:
                postfix += '_s'
        return postfix

    def reformatDir( self, path ):
        # adds '_compiler/' to the path and removes a possible '/obj'
        path = FileUtils.normDir( path, app.options.unixStyle )
        sep = FileUtils.getNormSep( app.options.unixStyle )
        if ( path.find( compilerVc6 + sep ) == -1 ):
            # add '_compiler' unless is a relative path
            #rec = re.compile( '[\\/.]*' )
            #m = rec.match( path )
            #if ( m ): predir = m.group()
            if ( path and path[0] != sep and not path.find( '..' ) == 0 ):  # i.e. not ( existing and at the beginning of the pahname )
                path = compilerVc6 + sep + path[:]
        # eliminates '/obj' because at this point it is annoying
        path = StringUtils.replace( path, sep + 'obj', '' )
        return path

    def extractOutputIntermDir( self, line ) :
        m = re_output_or_intermed_dir.match( line )
        if ( m ):
            subdir = m.group('subdir')
            dirname = self.reformatDir( subdir )
            if ( re_intermed_dir.match( line ) ):
                self.PropIntermeDirList[self.nCfg] = dirname
            else:
                self.PropOutputDirList[self.nCfg] = dirname
        return

    def extractMainOutDir( self, line ) :
        #if ( line.find( r'/out:' ) != -1 ):
        m = re_option_out_dir.search( line )
        if ( m ):
            outdir = m.group( 'subdir' )
            outdir = FileUtils.normPath( outdir, app.options.unixStyle )

            # Lib
            dirname = os.path.dirname( outdir )
            dirname =  FileUtils.normDir( dirname, app.options.unixStyle )
            self.OutputDirOutList[self.nCfg] = dirname

            basetitle = os.path.basename( outdir )
            (basetitle,ext) = os.path.splitext( basetitle )
            (ipf, basetitle) = self.getPostFixIndex( basetitle )
            if ( len( basetitle ) ):
                self.MainFileTitleBase          = basetitle
        else:
            msg = 'WARNING: the file \'%s\' has no \'/out:\' option in the configuration \'%s\'' % ( self.filename, self.configName )
            print msg

        return

    def addReformatOutputIntermediateDirs( self, line, subdir ):
        # reformat a line for Intermediate/Output directory - never remove it !
        changeSomething = ( app.options.reformatOutputIntermediateDirs == 1 )

        if ( changeSomething ):
            dirname = self.reformatDir( subdir ) # for debug
            if ( re_intermed_dir.match( line ) ):
                if ( self.PropIntermeDir != dirname ):
                    raise Exception( 'self.PropIntermeDir != dirname i.e. %s != %s' % ( self.PropIntermeDir, dirname) )
            else:
                if ( self.PropOutputDir != dirname ):
                    raise Exception( 'self.PropOutputDir != dirname i.e. %s != %s' % ( self.PropOutputDir, dirname) )
            line = StringUtils.replace( line, subdir, dirname )
        return line


    def changeOptionsCpp( self, line ):
        self.storedOptions = []

        changeSomething =   ( app.options.reformatOptionOutput  [self.c] != 0 ) or \
                            ( app.options.reformatOptionPdb     [self.c] != 0 ) or \
                            ( app.options.reformatOptionBrowse  [self.c] != 0 )
        if ( changeSomething ):
            if ( self.addKind == enum_ADD_CPP ):
                # the order of the following calls counts
                line = self.storeRemoveOptionOutputDir( line )
                line = self.storeRemoveOptionPdb( line )
                line = self.storeRemoveOptionBrowse( line )
                optionsList = [ '/D' ]
                index = self.findLastIndexInList( optionsList, line, False )
                if ( index == -1 ):
                    raise Exception( 'ADD CPP line without any /D option. Please improve the code or check the line.' )
            elif ( self.addKind == enum_SUBTRACT_CPP ):
                # the order of the following calls counts
                line = self.storeRemoveOptionBrowse( line )
                optionsList = [ '/Wx' ]
                index = self.findLastIndexInList( optionsList, line, True )

            line = self.addStoredOptions( line, index )

        # optimize can take more than one value and its place is before the /I option
        changeSomething =   ( app.options.reformatOptionOptimize[self.c] != 0 )
        if ( changeSomething ):
            if ( self.addKind == enum_ADD_CPP ):
                # the order of the following calls counts
                line = self.storeRemoveOptionOptimize( line )
                optionsList = [ '/I', '/D' ]
                index = self.findLastIndexInList( optionsList, line, False, True )
                if ( index == -1 ):
                    raise Exception( 'ADD CPP line without any good option to place close to. Please improve the code or check the line.' )

                line = self.addStoredOptions( line, index )

        return line

    def changeOptionsLnk( self, line ):
        self.storedOptions = []

        changeSomething =   ( app.options.reformatOptionOutput[self.c] == 1 ) or \
                            ( app.options.reformatOptionPdb   [self.c] != 0 )

        if ( changeSomething ):
            if ( self.addKind == enum_ADD_LINK32 ):
                # the order of the following calls counts
                line = self.storeRemoveOptionOutputDir( line )
                line = self.storeRemoveOptionPdb( line )
                optionsList = [ '/nologo', '/debug', '/dll', '/entry:', '/subsystem:', '/machine:' ]
                index = self.findLastIndexInList( optionsList, line, True )
                if ( index == -1 ):
                    raise Exception( 'ADD LINK32 line without any option between %s. Please improve the code or check the line.' % optionsList )
            elif ( self.addKind == enum_SUBTRACT_LINK32 ):
                 # the order of the following calls counts
                line = self.storeRemoveOptionPdb( line )
                optionsList = [ '/incremental:', '/map', '/pdb:' ]
                index = self.findLastIndexInList( optionsList, line, True )

            line = self.addStoredOptions( line, index )

        return line

    def changeOptionsLib( self, line ):
        self.storedOptions = []

        changeSomething =   ( app.options.reformatOptionOutput[self.c] == 1 )

        if ( changeSomething ):
            # the order of the following calls counts
            line = self.storeRemoveOptionOutputDir( line )
            optionsList = [ '/nologo' ]
            index = self.findLastIndexInList( optionsList, line, True )
            if ( index == -1 ):
                raise Exception( 'ADD LIB32 line without any option between %s. Please improve the code or check the line.' % optionsList )
            line = self.addStoredOptions( line, index )

        return line

    def changeOptionsBsc( self, line ):
        self.storedOptions = []

        changeSomething =   ( app.options.reformatOptionBrowse[self.c] == 1 )

        if ( changeSomething ):
            # the order of the following calls counts
            line = self.storeRemoveOptionBrowse( line )
            optionsList = [ '/nologo' ] # '# ADD BSC32' would give error: unbalanced parenthesis in the regexpr of findIndexCloseToOption()
            index = self.findLastIndexInList( optionsList, line, True )
            if ( index == -1 ):
                raise Exception( 'ADD BSC32 line without any option between %s. Please improve the code or check the line.' % optionsList )
            line = self.addStoredOptions( line, index )

        return line

    def findLastIndexInList( self, optionsList, line, ignorecase, before=False ):
        repeat = ( not before ) # these two options are not compatible and usually we want repeat = True unless before = True
        index = -1
        self.lastRegexGroupFound = '' # for debug only
        for i in range( len(optionsList)-1, -1, -1 ):
            option = optionsList[i]
            if ( ignorecase ):
                option = option.lower()
            idx = self.findIndexCloseToOption( line, option, ignorecase, before, repeat  )
            if ( before ):
                if ( index == -1 or ( idx != -1 and idx < index ) ):
                    index = idx
            else:
                if ( index < idx ):
                    index = idx

        return index

    def storeRemoveOptionOutputDir( self, line ):
        # reformat a line for output filename option ( /Fo /out: )
        # always convenient to specify the output dir for the object files, so never remove it !
        changeSomething = ( app.options.reformatOptionOutput[self.c] != 0 )
        if ( self.addKind == enum_ADD_CPP ):
            # (*) the reason why we always remove the '/Fo' option in a ADD CPP line is that vc6 always does it ( or at least when the value is the the same as Intermediate_Dir )
            addDir  = False
            addFile = False
            line = self.storeRemoveOption( line, '/Fo', self.PropIntermeDir, '', False, changeSomething, addDir, addFile )
        else:
            # this option should always be there ( we always want dir and filename specified for the linker output )
            addDir  = +1 # never remove it
            addFile = +1
            line = self.storeRemoveOption( line, '/out:', self.OutputDirOut, self.MainFileTitleBase + self.outputExt, False, changeSomething, addDir, addFile )
            
        if ( 0 < app.options.warning ):
            if ( self.appType == enumAppTypeExe and self.OutputDirOut != self.PropIntermeDir ):
                if ( not self.wdone_dirs_different and self.OutputDirOut == './' or self.OutputDirOut == '\\'  ):
                    self.wdone_dirs_different = True
                    print '  Warning!: the executable of %s has a LINK32 /out: directory different than the PROP_Output_Dir: [%s] != [%s]' % ( os.path.basename(self.filename), self.OutputDirOut, self.PropOutputDir )

        return line
    
    def storeRemoveOptionOptimize( self, line ):
        changeSomething = ( app.options.reformatOptionOptimize[self.c] and app.options.reformatOptionOptimize[self.c] != '0' )
        if ( self.addKind == enum_ADD_CPP and changeSomething ):
            # we always add / replace something; never delete anything
            addDir  = changeSomething
            addFile = addDir # we usually want both in the same way
            option = '/' + app.options.reformatOptionOptimize[self.c]
            for opt in [ '/O1', '/O2', '/Od' ]:
                line = self.storeRemoveOption( line, opt, '', '', False, changeSomething, addDir, addFile, False )
            self.storedOptions.append( option )
        return line
        
    def storeRemoveOptionPdb( self, line ):
        # reformat a line for ProgramDatabase option ( /Fd /pdb: )
        changeSomething = ( app.options.reformatOptionPdb[self.c] != 0 )
        if ( self.addKind == enum_ADD_CPP ):
            # (*) the reason why we always remove the '/Fd' option in a ADD CPP line is that vc6 always does it ( or at least when the value is the the same as the output project aside the extension )
            if ( self.appType == enumAppTypeExe ):
                addDir  = False
                addFile = False # we usually want both in the same way
                line = self.storeRemoveOption( line, '/Fd', self.OutputDirOut, '', False, changeSomething, addDir, addFile )
            else:
                if ( self.appType == enumAppTypeLib ):
                    addDir  = app.options.reformatOptionPdb[self.c]
                    addFile = addDir# we usually want both in the same way
                else:
                    addDir  = False # ?
                    addFile = addDir# we usually want both in the same way
                # for DLL's and Lib's also the filename is specified (and the link option '/pdb:' does not exist)
                line = self.storeRemoveOption( line, '/Fd', self.OutputDirOut, self.MainFileTitleBase + '.pdb', False, changeSomething, addDir, addFile )
        elif ( self.addKind == enum_ADD_LINK32 or self.addKind == enum_ADD_LIB32 ):
            # (*) the reason why we always remove the '/pdb' option in a ADD LINK32 line is that vc6 always does it ( or at least when the value is the the same as the output project aside the extension )
            addDir  = False
            addFile = False # we usually want both in the same way
            line = self.storeRemoveOption( line, '/pdb:', self.OutputDirOut, self.MainFileTitleBase + '.pdb', False, changeSomething, addDir, addFile )

            if ( self.addKind == enum_ADD_LINK32 ):
                addDir  = app.options.reformatOptionPdb[self.c]
                addFile = addDir # we usually want both in the same way
                line = self.storeRemoveOption( line, '/debug', '', '', False, changeSomething, addDir, addFile )
                
        elif ( self.addKind == enum_SUBTRACT_LINK32 ):
            # '/debug' in # SUBTRACT LINK32 disable the pdb option
            addDir  = -(app.options.reformatOptionPdb[self.c]) # /debug in the SUBTRACT line has opposite meaning
            addFile = addDir # we usually want both in the same way
            line = self.storeRemoveOption( line, '/debug', '', '', False, changeSomething, addDir, addFile )
        return line

    def storeRemoveOptionBrowse( self, line ):
        # reformat a line for Browse database option ( /FR /Fr /o: )
        changeSomething = ( app.options.reformatOptionBrowse[self.c] != 0 )
        addDir  = app.options.reformatOptionBrowse[self.c]
        addFile = addDir # we usually want both in the same way
        if ( self.addKind == enum_ADD_CPP ):
            line = self.storeRemoveOption( line, '/FR', self.PropIntermeDir, '', True, changeSomething, addDir, addFile )
        elif ( self.addKind == enum_ADD_LINK32 or self.addKind == enum_ADD_LIB32 ):
            # the bsc file will be placed in the same dir of the main output
            line = self.storeRemoveOption( line, '/o', self.OutputDirOut, self.MainFileTitleBase + '.bsc', False, changeSomething, addDir, addFile )
        elif ( self.addKind == enum_SUBTRACT_CPP ):
            # /Fr' in # SUBTRACT CPP disable the pdb option
            addDir  = -(app.options.reformatOptionBrowse[self.c]) # /debug in the SUBTRACT line has opposite meaning
            addFile = addDir # we usually want both in the same way
            line = self.storeRemoveOption( line, '/FR', '', '', True, changeSomething, addDir, addFile )
        return line

    def storeRemoveOption( self, line, option, directory, filename, ignorecase, changeSomething, addDir, addFile, store=True ):
        # Remark: this function removes the entry even if changeSomething = False !
        #           because we want to set a 'standard' order of the options
        #           Therefore if we don't want to change anything we need not to call this function
        # addDir and addFile with value: = +1 => add and with = -1 => remove
        # if ( directory and filename == empty ) then the option alone is added /removed

        fn = ''
        if ( addFile and filename ):
            fn = filename
            if ( fn ):
                (fn,ext) = os.path.splitext( fn )
                (ipf, basetitle) = self.getPostFixIndex( fn )
                if ( ipf != -1 ):
                    fn = fn[:ipf]
                fn += self.getPostFix()
                fn += ext

        dr = ''
        if ( addDir and directory ):
            dr = directory

        if ( addDir == +1 or addFile == +1 ):
            if ( dr or fn ):
                replac = ( option + '\"' + dr + fn + '\"' + ' ' )
            else:
                # we meant to just add/remove the opion alone
                replac = option
        else:
            replac = ''

        # first remove the option ( so it will go in a 'standard' position
        #(?P<fulloption> /Fo(\s*?)"(?P<optionarg>[a-zA-Z0-9_ $\(\)\\/.]*)") | (?P<optionalone> /Fo(\s+?))
        reOption = re.VERBOSE
        if ( ignorecase ): reOption += re.IGNORECASE
        if ( option and option[ len(option) -1 ] == ':' ):
            # (/Fd:"vc6\Debug\Beautiful Actions_vc6.pdb") or /machine:i386 ( but no spaces )
            rec = re.compile( r'(?P<fulloption> %s(\s*?)"(?P<optionarg>[a-zA-Z0-9_ $\(\)\\/.]*)") | (?P<fulloption2> %s(?P<optionarg2>[a-zA-Z0-9_$\(\)\\/.]*))' % (option,option), reOption )
        else:
            # (/Fd "vc6\Debug\Beautiful Actions_vc6.pdb") or /FR ) ( isolated option with no argument )
            rec = re.compile( r'(?P<fulloption> %s(\s*?)"(?P<optionarg>[a-zA-Z0-9_ $\(\)\\/.]*)") | (?P<optionalone> %s(\s+?))' % (option,option), reOption )

        # remove the option and store it
        s = ''
        m = rec.search( line )
        if ( m ):
            # option found; remove it
            # Remark: line = rec.sub( replac, line ) # this doesn't work right !
            s = m.group()
            if ( s ):
                i = line.find( s )
                ls = len(s)
                c = s[-1]
                if ( c == '\r' or c == '\n' ):
                    s = s[:-1]
                    ls -= 1
                #if ( replacing ):
                #    c = line[i+ls:]
                #    if ( c == ' ' or c == '\t' or c == '\r' or c == '\n' ):
                #        replac = replac[:-1]    # get rid of the last space
                #    line = line[:i] + replac + line[i+ls:]
                line = line[:i] + line[i+ls:]  # remove
        self.lastRegexGroupFound = s

        if ( store ):
            if ( changeSomething ):
                # because not to append is like to remove
                self.storedOptions.append( replac )
            else:
                # when some s or when the list is empty
                if ( s or len(self.storedOptions) == 0 ):
                    self.storedOptions.append( s )

        return line

    def addStoredOptions( self, line, index ):
        addString = ' ' # this space make sure the added options are separated from the previous one
        for fullOption in self.storedOptions:
            addString += fullOption + ' '
            
        self.storedOptions = [] # reset what once it is done
        
        i = index
        if ( i != -1 ):
            #inserting
            #if ( 0 < i and line[i-1] != ' ' and line[i-1] != '\t' ):
            #    addString = ' ' + addString[:]
            if ( i == len( line ) ):
                # safety measure
                ( i, crlf ) = StringUtils.getEol( line )
            line = line[:i] + addString + line[i:]
        else:
            #appending ( before the eol ( crlf ) )
            ( i, crlf ) = StringUtils.getEol( line )
            #if ( 0 < ln and line[i-1] != ' ' and line[i-1] != '\t' ):
            #    addString = ' ' + addString[:]
            line = line[:i] + addString + crlf

        #self.storedOptions = []

        return line

    def findIndexCloseToOption( self, line, option, ignorecase, before, repeat ):
        backward = False

        if ( ignorecase ):
            line   = line.lower()
            option = option.lower()

        # This accepts:
        # /D "BUILD_APPKIT_LIB" /FR /Yu"ApplicationKit.h"
        # but also
        # /D "BUILD_APPKIT_LIB" /FR"vc6\DebugDLL\" /Yu"ApplicationKit.h"
        reOption = re.VERBOSE
        if ( ignorecase ): reOption += re.IGNORECASE
        if ( option and option[ len(option) -1 ] == ':' ):
            # (/Fd:"vc6\Debug\Beautiful Actions_vc6.pdb") or /machine:i386 ( but no spaces )
            rec = re.compile( r'(?P<fulloption> %s(\s*?)"(?P<optionarg>[a-zA-Z0-9_ $\(\)\\/.]*)") | (?P<fulloption2> %s(?P<optionarg2>[a-zA-Z0-9_$\(\)\\/.]*))' % (option,option), reOption )
        else:
            # (/Fd "vc6\Debug\Beautiful Actions_vc6.pdb") or /FR ) ( isolated option with no argument )
            rec = re.compile( r'(?P<fulloption> %s(\s*?)"(?P<optionarg>[a-zA-Z0-9_ $\(\)\\/.]*)") | (?P<optionalone> %s(\s+?))' % (option,option), reOption )
        index =  -1

        s = ''
        if ( backward ):
            raise Exception( 'please replace backward with other options combinations. A Regex is necessary.' )
            #index = line.rfind( option )
            #if ( index != -1 ):
            #    lin = line[ index:]
            #    m = rec.search( lin )
            #    if ( m ):
            #        s = m.group()
        else:
            m = rec.search( line )
            if ( m ):
                s = m.group()
                c = s[-1]
                if ( c == '\r' or c == '\n' ):
                    s = s[:-1]
                self.lastRegexGroupFound = s

        if ( s ):
            index = line.find( s )
            if ( not before ):
                ls = len( s )
                index += ls

            if ( before ):
                if ( 0 < index and index < len(line) ):
                    c = line[index-1]
                    if ( c == ' ' or c == '\t' ):
                        index -= 1
            else:
                if ( index != -1 and index < len(line) ):
                    c = line[index]
                    if ( c == ' ' or c == '\t' ):
                        index += 1

            if ( repeat and index != -1 ):
                if ( repeat ):
                    if ( backward != before ):
                        raise Exception( 'findIndexCloseToOption( line, %s, %d, %d, %d ): repeat wants backward == before otehrwise infinite loop ( backward == %s )!' % ( option, ignorecase, before, repeat, backward ) )
                idx = index
                if ( backward ):
                    lin = line[:idx]
                else:
                    lin = line[idx:]
                while ( True ):
                    # recursion
                    idx = self.findIndexCloseToOption( lin, option, ignorecase, before, False )
                    if ( idx == -1 ):
                        break
                    else:
                        if ( backward ):
                            lin = lin[:idx]
                            index = idx
                        else:
                            index += idx
                            lin = lin[idx:]
                    continue

        return index


class Walker:
    """Directory Walker class
    This class is introduced only in order to prevent that the variables in __main__ be seen as global
    which is leading to errors difficult to find
    """
    def __init__(self):
        pass

    def walk_files( self, root, recursive=False ):
        # non recursive implementation at all
        #def walk_files(top):
        #    names = os.listdir(top)
        #    for name in names:
        #        if os.path.isfile(name):
        #            yield name
        for path, dirs, files in os.walk(root):
            for fn in files:
                #if ( not recursive ):       # this doesn't work !
                #    if ( path != '.' ):     # this doesn't work !
                #        continue            # this doesn't work !
                yield os.path.join(path, fn)
            if not recursive:                               # this doesn't work !
                break # break or return is not enough !     # this doesn't work !
        return

    def job( self ):
        singleFile = ( app.options.filename != '' )
        
        self.manageProjects()
        
        if ( not singleFile ):
            self.conformLibraries()
            self.createWorkspaces()
            self.duplicateWorkspaces()
            
        return

    def manageProjects( self ):
        if ( app.options.prompt ):
            raw_input( '\n  Press enter to continue ( Ctrl+C to exit ) ... ')

        # it is not accepted in a different way under cygwin
        #app.currentdir = app.currentdir.replace( '\\', '/' )
        #app.currentdir = app.currentdir.replace( '//', '/' )
        os.chdir( app.currentdir )

        app.allProjectNamesList = []
        app.allProjectPathsList = []
        app.allProjectNamesLwrDict = {}

        sep = FileUtils.getNormSep( app.options.unixStyle )

        singleFile = ( app.options.filename != '' )

        app.changedFiles   = 0
        app.unchangedFiles = 0
        app.createdFiles   = 0
        nFiles = 0
        for filename in self.walk_files( root, app.options.recurse ):
            if ( len(filename) > 4 and filename[-4:] == '.dsp' ):
                # skip filenames like: file_vc70.dsp or file_vc71.dsp
                filename = FileUtils.normPath( filename, app.options.unixStyle )

				#JC - I added some extra code to skip over file_icl7.dsp as well!
                if ( app.options.enableVcfSpecific ):
                    fn = filename.lower()
                    if ( ( fn.find( '_' + compilerVc70 ) != -1 ) or ( fn.find( '_' + compilerVc71 ) != -1 ) or ( fn.find( '_' + compilerIcl7 ) != -1 ) ):
                        continue
                    if ( ( fn.find( compilerVc70 + sep ) != -1 ) or ( fn.find( compilerVc71 + sep ) != -1 ) or ( fn.find( compilerIcl7 + sep ) != -1 ) ):
                        continue

                doIt = app.checkAllowedDir( filename )
                if ( doIt and singleFile ):
                    doIt = ( filename.lower().find( app.options.filename.lower() ) != -1 )


                if ( doIt ):
                    nFiles += 1

                    fullname = os.path.join( root, filename )
                    fullname = FileUtils.normPath( fullname, app.options.unixStyle )

                    if ( backupFiles ):
                        FileUtils.backup( fullname )
                    if ( 0 < app.options.verbose ):
                        print FileUtils.relativePath( app.currentdir, fullname, True, app.options.unixStyle )
                    dsp = DspFile( app, fullname )
                    dsp.reformat()

                    prjName = dsp.getTrueProjectName()
                    app.allProjectNamesList.append( prjName )
                    app.allProjectNamesLwrDict[ prjName.lower() ] = prjName
                    absPrjPath = FileUtils.absolutePath( app.currentdir, root + sep + fullname, app.options.unixStyle )
                    app.allProjectPathsList.append( absPrjPath )

                    if ( app.options.enableVcfSpecific ):
                        dsp.duplicateVcs()

        if ( 0 < app.options.verbose ):
            print ' %s dsp files processed. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.changedFiles, app.unchangedFiles, app.createdFiles)

        return

    def conformLibraries( self ):
        if ( app.options.conformLibraries ):
            workspaceName = FileUtils.absolutePath( app.currentdir, 'dummy', app.options.unixStyle )
            workspaceCL = Workspace( workspaceName )
            workspaceCL.conformAllLibraries()
        return

    def createWorkspaces( self ):
        if ( app.options.enableVcfSpecific and app.options.createWorkspaces ):
            # creates
            for workspaceName in app.createWorkspacesList:
                workspacePath = FileUtils.absolutePath( app.currentdir, workspaceName, app.options.unixStyle )
                workspace = Workspace( workspacePath )
                ( workspaceName, ext ) = os.path.splitext( os.path.basename( workspacePath ) )
                workspaceName = workspaceName.lower()
                workspace.create( app.allProjectNamesList, app.allProjectPathsList, g_tableFilterWorkspacesCreation[workspaceName], True )
                workspace.duplicateVcs( False )
        return

    def duplicateWorkspaces( self ):
        if ( app.options.enableVcfSpecific and app.options.duplicateWorkspaces ):
            #blackBoxWorkspaceName = './BlackBox/BlackBox.dsw'
            #xmakeWorkspaceName    = './xmake/xmake.dsw'
            for workspaceName in app.duplicateWorkspacesList:
                workspacePath = FileUtils.absolutePath( app.currentdir, workspaceName, app.options.unixStyle )
                workspace = Workspace( workspacePath )
                workspace.duplicateVcs( True )
        return



if __name__ == '__main__':
    root = '.'

    app = DspApp()

    walker = Walker()
    walker.job()

    pass


#######################################################################################################################
"""
Notes:
    1) The modified files in the safest way for the originals
        First is created a temporary file and then, if everything is ok, it is renamed into the original one

    2) The order of the options is mantained: but if the vc6 options are in the wrong order
        and th this script's option is not null, then the order is changed in a 'standard' way

    3) The output file has the format basename_compiler_[|d|sd]
            Where d with debug and s for static libraries
            compiler is = [ vc6 | vc70 | vc71 ]

    4) The bsc file will be placed in the same dir of the main output

    5) reformatOptionOutput = d:-1, r:-1
        this option affects only the /Fo option
        the linker option /out: instead is so important that the script always garuantees that it is there in the dsp files
        
    6) For /pdb /debug  infos see the other notes below

    7) The way a configuration of a dsp project is considered debug versus release is still naive
        so it might fail if a user doesn't call it Debug
        This can be easily fixed. See the function checkSetDebug

Limitations:
    1) The options work better form the configuration files
        because I didn't look yet on how get options from the command line without argument

    2) A program database option is mosly enabled/disabled by the /debug option ( generate debug info )
        which is present or in the #ADD LINK32 line or in the #SUBTRACT LINK32 line
        But this program doesn't affect (create) any SUBTRACT line if it doesn't exist yet
        
    3) It is possible to change the option from unixStyle = True --> False
        but then it wouldn't work under Cygwin
        
        
        
Other notes on some Visual Studio options:
    
    1) Program Database / Debug informations
        /debug linker option activates debug informations
        Once you have /debug you can only choose where to place those infos,
        so the debug footprint will be the same, unless you put those infos in the pdb files and then you delete them
        
        The linker option /PDB:NONE specify that they are not placed in any pdb files. They go directly into the EXEcutable or DLL
        The linker option /PDB:filename.pdb specify instead that the EXEcutable or DLL contains only a link to where the pdb files is placed
        
        The debugging informations ( minimal or not ) are necessary for the linker.
        The compiler option /Zd and /Z7 make the debugging informations to be embedded into the obj files.
        The compiler option /Zi and /ZI make the debugging informations to be embedded into a pdb file
        The compiler option /Fd only lets me to determine the name of the pdb file. Nothing else.
        
        That's all.
        As consequence of that:
        a) If you don't want any pdb files around, you need to use /Zd or /Z7 together with /PDB:NONE
        b) If you use /Zi or /ZI and you distribute a static library, you need to distribute the pdb files too.
           Important: under vc7 if you use /Zi or /ZI without the option /Fd you'll have warnings like:
            # libAGG_vc70_sd.lib(agg_affine_matrix.obj) : warning LNK4204: 'd:\Projs\GShell\Libraries\Vcf\vcf-active\examples\SketchIt\vc70\Debug\vc70.pdb' is missing debugging information for referencing module; linking object as if no debug info
            each time you compile a program with the /debug linker option to that library               
        
"""

