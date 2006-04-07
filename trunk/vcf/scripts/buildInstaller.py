#!/usr/bin/env python
#
# Author: Jim Crafton
#
# build installer python script!



"""
"""

import sys
import os
import os.path
import shutil
import filecmp
import ConfigParser
import re
import string

# globals



def main():
	
	ISS = "\"c:/Program Files/Inno Setup 4/ISCC.exe\""

	VCF_VERSION=''
	VCF_VERSION_STAGE= ''
	FULL_VCF_VERSION=''
	FULL_VCF_DOT_VERSION=''

	INSTALL_FILE_LISTING= '../installers/win32/vcfSrcFiles.iss'
	INSTALL_FILE = '../installers/win32/VCFFullInstaller.iss'
	



	fs = file( '../VERSION', 'r' )
	lines = fs.readlines()
	VCF_VERSION = string.strip(lines[0])
	fs.close()
	
	
	fs = file( '../VERSION_STAGE', 'r' )
	lines = fs.readlines()
	
	VCF_VERSION_STAGE = string.strip(lines[0])
	fs.close()
	
	
	FULL_VCF_VERSION = VCF_VERSION + ' ' + VCF_VERSION_STAGE
	FULL_VCF_DOT_VERSION = VCF_VERSION + '-' + VCF_VERSION_STAGE
	
	if ( len(sys.argv) > 1 ) : 
		arg1 = sys.argv[1:][0]
		if ( arg1 == "src" ) :
			print "Building source only installer!"
			INSTALL_FILE = '../installers/win32/VCFFullInstallerNoBin.iss'
	
	os.chdir( '../installers/win32' )
	
	if os.path.exists( 'vcfSrcFiles.iss' ) :
		os.remove( 'vcfSrcFiles.iss' )
	
	print( 'preparing list of all files for distribution in installer...' )
	SRC_DIRS= "../../src", "../../build"
	
	extensions = [".h", '.hpp', '.c', '.dsw', '.dsp', '.bmp', '.rgs', '.rc', '.xml', '.idl',
			'.def', '.vcfdir', '.vcp', '.ico', '.rc2', '.odl', '.inl',
			'.vff', '.inf', '.vcproj', '.sln', '.cpp', '.CPP', '.HPP', '.cxx', '.CXX',
			'.cur', '.CUR', '.mak', '.txt', '.vsdir', '.vsz', '.js', '.gif', '.htm', '.css',
			'.bkl', '.inc', '.bcc', '.bpf', '.bpr', '.cbp', '.workspace', '.vc', '.gcc', '.gnu', 
			'.bkgen', '.dat', '.cfg', '.png', '.xsl', '.py']

	
	
	exampleExtensions = [ '.h', '.cpp', '.CPP', '.dsw', '.dsp', '.bmp', '.rgs', '.rc', '.idl',
			   '.def', '.ico', '.rc2', '.odl', '.vff', '.html', '.xml', '.vcproj', '.sln',
				'.bkl', '.inc', '.bcc', '.bpf', '.bpr', '.cbp', '.workspace', '.vc', '.gcc',
				'.bpg', '.png', '.mov', '.strings', '.vp', '.txt', '.hpp', '.yy', '.ll', '.hhp',
				 '.js', '.css', '.bat', '.gif', '.hhk', '.hhc', '.plist' ]


	
	srcFiles = []
	
	reStr = ""	
	for ext in extensions :
		if reStr == "" :
			reStr = '(.*\\' + ext + '$)'
		else :
			reStr = reStr + '|(.*\\' + ext + "$)"
	
	reStr = reStr + '|(.*\\GNUmakefile' + "$)"
	reStr = reStr + '|(.*\\Makefile' + "$)"
	reStr = reStr + '|(.*\\README' + "$)"




	fileTest = re.compile( reStr, re.IGNORECASE )
	
	cvsTest = re.compile( ".*\/CVS" )

	buildLogTest = re.compile( "BuildLog.htm", re.IGNORECASE )
	
	for dir in SRC_DIRS :
		for root, dirs, files in os.walk( dir ):
			if not cvsTest.match( root ) :
				print ( 'Scanning ' + root + "..." ) 
				for afile in files :
					if  fileTest.match( afile ) and not buildLogTest.match( afile ) :
						srcFiles.append( os.path.join( root, afile ) )
				
				
				
			
	
	reStr = ""	
	for ext in exampleExtensions :
		if reStr == "" :
			reStr = '(.*\\' + ext + '$)'
		else :
			reStr = reStr + '|(.*\\' + ext + "$)"

	reStr = reStr + '|(.*\\GNUmakefile' + "$)"

	fileTest = re.compile( reStr, re.IGNORECASE )
	exampleFiles = []
	
	for root, dirs, files in os.walk( "../../examples" ):
		if not cvsTest.match( root ) :
			print ( 'Scanning Examples ' + root + "..." ) 
			for afile in files :
				if  fileTest.match( afile ) :
					exampleFiles.append( os.path.join( root, afile ) )
						
	
	
	dirFront = "..\\..\\"
	destDir = ""
	srcFile = ""
	vcfSrcFiles = "";
	
	count = len(srcFiles)
	count = count + len(exampleFiles)
	
	print "Installation will include  ",  count,  " file(s)."
	
	for afile in srcFiles :
		srcFile = string.replace( afile,  "/", "\\" );
		destDir = string.replace( os.path.dirname( afile ),  "/", "\\" )
		destDir = string.replace( destDir, dirFront, "" )
		line = "Source: " + srcFile + "; DestDir: {app}\\" + destDir + "; Components: Src\r\n"
		vcfSrcFiles = vcfSrcFiles + line;
		
	vcfSrcFiles = vcfSrcFiles + "\r\n;\r\n;Examples\r\n;\r\n\r\n"
	
	for afile in exampleFiles :
		srcFile = string.replace( afile,  "/", "\\" );
		destDir = string.replace( os.path.dirname( afile ),  "/", "\\" )
		destDir = string.replace( destDir, dirFront, "" )
		line = "Source: " + srcFile + "; DestDir: {app}\\" + destDir + "; Components: Examples\r\n"
		vcfSrcFiles = vcfSrcFiles + line;
	
	
	
	print "Writing out file listing..."
	
	fs = file( 'vcfSrcFiles.iss', 'w' )
	fs.write( vcfSrcFiles )
	fs.close()
	
	print "Installation file listing is complete, all files stored in vcfSrcFiles.iss."	
	
	os.chdir( '../../scripts' );	
	
	print ( 'Starting build of all binaries and installation executable for' )
	print ( 'Visual Component Framework ' + FULL_VCF_DOT_VERSION )
	print os.getcwd()
	
	print "Building Debug binaries..."
	#os.system( "msdev ../build/vc60/vcfAllProjects.dsw /MAKE \"vcfAllLibs - Win32 Debug\" /REBUILD /OUT vcfAll-debug.stat.log" )
	print "Done building Debug binaries. Read vcfAll-debug.stat.log for more."
	
	print "Building Release binaries..."
	#os.system( "msdev ../build/vc60/vcfAllProjects.dsw /MAKE \"vcfAllLibs - Win32 Release\" /REBUILD /OUT vcfAll-release.stat.log" )	
	print "Done building Release binaries. Read vcfAll-release.stat.log for more."
	
	print "Building VC6 Add-in binaries..."
	os.system( "msdev ../build/vc60/add-ins/all.dsw /MAKE \"all - Win32 Release\" /REBUILD /OUT vcfAddins-release.stat.log" )
	print "Done building VC6 Add-in binaries. Read vcfAddins-release.stat.log for more."
	
	print "Building MSDNIntegrator binaries..."
	os.system( "msdev ../src/thirdparty/win32/MSDNIntegrator/MSDNIntegrator.dsw /MAKE \"MSDNIntegrator - Win32 Release\" /REBUILD /OUT MSDNIntegrator-release.stat.log" )
	print "Done building MSDNIntegrator binaries. Read MSDNIntegrator-release.stat.log for more."
	
	print "Building RegEnVar binaries..."
	os.system( "msdev ../src/thirdparty/win32/RegEnVar/RegEnVar.dsw /MAKE \"RegEnVar - Win32 Release\" /REBUILD /OUT RegEnVar-release.stat.log" )
	print "Done building RegEnVar binaries. Read RegEnVar-release.stat.log for more."

	
	print "Done building binaries, preparing to build installer."
		
	shutil.copyfile( INSTALL_FILE, INSTALL_FILE + ".bak" )
	print "backing up original installer file (backed up to " + INSTALL_FILE + ".bak)"

	fs = file( INSTALL_FILE, 'r' )
	
	lines = fs.readlines()
	fs.close()
	
	lines2 = []
	for line in lines :
		line = string.replace( line,  "VCF-VERSION", VCF_VERSION )
		line = string.replace( line,  "VCF-LONG-VERSION", FULL_VCF_VERSION )
		lines2.append( line )	
	
	
	fs = file( INSTALL_FILE, 'w' )
	fs.writelines( lines2 )
	fs.close()
	
	print "Applying modifications to installer file to update to correct version (" + VCF_VERSION + ")"
	
	os.system( ISS + " " + INSTALL_FILE )	
	
	print "Restoring installer file from backup file"
	shutil.copyfile( INSTALL_FILE + ".bak", INSTALL_FILE )
	
	return
 

if __name__ == '__main__':
    main()
	
    pass