import os.path
import mk

# Here we try to read preferred option values from ~/.vcf/config.<ext>,
# where <ext> is an extension peculiar to the current format.
opts = {}
if mk.vars['FORMAT_SUPPORTS_CONDITIONS'] == '1':
    config = os.path.join( os.path.expanduser( '~' ), '.vcf' + os.path.sep + 'config' )
    exts = { 'msvc':'.vc', 'mingw':'.gcc', 'borland':'.bcc', 'gnu':'.gnu', \
             'dmars_smake':'.dms', 'dmars':'.dmc', 'watcom':'.wat' }
    ext = exts[mk.vars['FORMAT']]
    if ext:
        config += ext
        if os.path.exists( config ) and os.path.isfile( config ):
            print config
            f = open( config )
            line = f.readline()
            while line:
                i = line.find( '#' )
                if i >= 0:
                    line = line[:i]
                line = line.strip()
                if line:
                    line = line.split( '=', 1 )
                    if len( line ) == 2:
                        line[0] = line[0].strip()
                        line[1] = line[1].strip()
                        opts[ line[0] ] = line[1]
                line = f.readline()
            f.close()


# Returns a string that represents a filename of the given library name.
def getFilename( libName ):
    return '%s$(SUFFIX_SELECTLIB)$(SUFFIX_LIBRARY)' % libName

# Returns a string that represents a filename of the given static library name.
def getLibFilename( libName ):
    return '%s$(SUFFIX_SELECTLIB)$(SUFFIX_STATIC)' % libName

# Returns a string that represents a filename of the given dynamic library name.
def getDllFilename( libName ):
    return '%s$(SUFFIX_SELECTLIB)$(SUFFIX_DYNAMIC)' % libName

# Returns the quoted given parameter.
def getQuoted( text ):
    if text.startswith( '"' ) and text.endswith( '"' ):
        return text
    else:
        return '"%s"' % text

# Returns the unquoted given parameter.
def getUnquoted( text ):
    if text.startswith( '"' ) and text.endswith( '"' ):
        return text[1:-1]
    else:
        return text

# Joins two parts of a path and returns a result path. Whether the result is 
# quoted or not depends on a value of the VCF_INTERNAL variable.
def joinPaths( firstPart, secondPart ):
    result = os.path.join( getUnquoted( firstPart ), getUnquoted( secondPart ) )
    if mk.vars['VCF_INTERNAL'] == '0':
        return getQuoted( result )
    else:
        return result

# Returns a value of the given option.
# If there is a preferred value for the given option it will be returned.
# Otherwise the given default value will be returned.
def getOptionValue( option, defaultValue ):
    if len( opts ) > 0:
        preferred = opts[option]
        if preferred and preferred != defaultValue:
            print '\t%s: %s => %s' % ( option, defaultValue, preferred )
            return preferred
    return defaultValue
