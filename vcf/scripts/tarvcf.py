#!/usr/bin/env python
#
# Author: Jim Crafton
#
# source  installer python script!



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
	
	VCF_VERSION=''
	VCF_VERSION_STAGE= ''
	FULL_VCF_VERSION=''
	FULL_VCF_DOT_VERSION=''

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
	
	
	os.chdir( '../' )
	
	
	print( 'preparing list of all files for distribution in installer...' )
	SRC_DIRS= "./src", "./build"
	
	extensions = [".h", '.hpp', '.c', '.dsw', '.dsp', '.bmp', '.rgs', '.rc', '.xml', '.idl',
			'.def', '.vcfdir', '.vcp', '.ico', '.rc2', '.odl', '.inl',
			'.vff', '.inf', '.vcproj', '.sln', '.cpp', '.CPP', '.HPP', '.cxx', '.CXX',
			'.cur', '.CUR', '.mak', '.txt', '.vsdir', '.vsz', '.js', '.gif', '.htm', '.css',
			'.bkl', '.inc', '.bcc', '.bpf', '.bpr', '.cbp', '.workspace', '.vc', '.gcc', '.gnu', 
			'.bkgen', '.dat', '.cfg', '.png', '.xsl', '.py', '.msg', '.tbl']

	
	
	exampleExtensions = [ '.h', '.cpp', '.CPP', '.dsw', '.dsp', '.bmp', '.rgs', '.rc', '.idl',
			   '.def', '.ico', '.rc2', '.odl', '.vff', '.html', '.xml', '.vcproj', '.sln',
				'.bkl', '.inc', '.bcc', '.bpf', '.bpr', '.cbp', '.workspace', '.vc', '.gcc',
				'.bpg', '.png', '.mov', '.strings', '.vp', '.txt', '.hpp', '.yy', '.ll', '.hhp',
				 '.js', '.css', '.mak', '.bat', '.gif', '.hhk', '.hhc', '.dat', '.scan', '.tab', '.plist' ]


	
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
	
	svnTest = re.compile( ".*\/\.svn" )

	buildLogTest = re.compile( "BuildLog.htm", re.IGNORECASE )
	
	for dir in SRC_DIRS :
		for root, dirs, files in os.walk( dir ):
			if not svnTest.match( root ) :
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
	
	for root, dirs, files in os.walk( "./examples" ):
		if not svnTest.match( root ) :
			print ( 'Scanning Examples ' + root + "..." ) 
			for afile in files :
				if  fileTest.match( afile ) :
					exampleFiles.append( os.path.join( root, afile ) )
						
	
	
	tarFiles = "";
	
	count = len(srcFiles)
	count = count + len(exampleFiles)
	
	print "Found  ",  count,  " file(s) to archive."
	
	for afile in srcFiles :
		tarFiles = tarFiles + afile + "\n";
	
	
	for afile in exampleFiles :
		tarFiles = tarFiles + afile + "\n";	
	
	
	print "Writing out file listing..."
	
	fs = file( 'tarfilelisting.txt', 'w' )
	fs.write( tarFiles )
	fs.close()
	
	print "Archive file listing is complete, all files stored in tarfilelisting.txt."	
	
	print "creating tmp archive directory..." 
	tmpdir = "tmp/vcf-" + VCF_VERSION + "/"
	tarfile = tmpdir + "tmp.tar"

	os.mkdir( "tmp/" )	
	os.mkdir( tmpdir )	
	os.system( "tar -cf " + tarfile + " -T tarfilelisting.txt" )
	os.system( "tar -xf " + tarfile + " -C " + tmpdir )
	
	os.remove( "tarfilelisting.txt" )
	os.remove( tarfile )
	
	os.system( "cp --parents readme.* " + tmpdir )
	os.system( "cp --parents quickbuild.* " + tmpdir )
	os.system( "cp --parents license.txt " + tmpdir )

	print "Creating tar file..."
	
	os.chdir( 'tmp/' )
	
	os.system( "tar -cf vcf-" + VCF_VERSION + ".tar vcf-" + VCF_VERSION + "/" )

	print "Compressing tar file with gzip..."
	
	os.system( "gzip -f vcf-" + VCF_VERSION + ".tar" )
	tarfile = ""
	
	if os.path.exists( "../uploadToSF" ) :
		tarfile = "../uploadToSF/vcf-" + VCF_VERSION + ".tar.gz"		
	else :
		tarfile = "../vcf-" + VCF_VERSION + ".tar.gz"
	
	print "Moving tar file to: " + tarfile
	os.rename( "vcf-" + VCF_VERSION + ".tar.gz", tarfile )
	
	os.chdir( '../' )

	print "Removing tmp directory."
	os.system( "rm -rf tmp/" )
	
	return
 

if __name__ == '__main__':
    main()
	
    pass