<!--
Copyright (c) 2000-2003, Jim Crafton
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
	Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

NB: This software will not save the world.
CVS Log info
$Log$
Revision 1.3  2003/12/18 05:15:52  ddiego
merge from devmain-0-6-2 branch into the stable branch

Revision 1.2.4.3  2003/12/17 05:11:56  ddiego
minors mods, mostly to support chnages to the installer and some
problems with the html help docs abnd MSDN integration

Revision 1.2.4.2  2003/12/16 03:47:44  ddiego
some changes to documentation and a few minor changes to class wiz's

Revision 1.2.4.1  2003/09/29 03:45:38  ddiego
added some further tweaks to update the docs with the upcoming
website revision.

Revision 1.2  2003/05/17 20:36:55  ddiego
this is the checkin for the 0.6.1 release - represents the merge over from
the devmain-0-6-0 branch plus a few minor bug fixes

Revision 1.1.2.1  2003/03/24 06:05:02  ddiego
more additions to the doc makefile and for allowing for online doxygen
generation


-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	        version="1.0">
 
	 <!--
	 this uses a local path - may need to be modified for others
	 -->
 
	 <xsl:import href="vcf.xsl"/>

	<xsl:param name="htmlhelp.hhc.generate.source.chm.link" select="0"/>
	<xsl:param name="htmlhelp.hhc.binary" select="1"/>
	<xsl:param name="htmlhelp.hhp" select="'vcf-docbook-with-src.hhp'"></xsl:param>

	<xsl:param name="htmlhelp.chm" select="'vcf-docbook-with-src.chm'"/>
	
<xsl:param name="htmlhelp.hhp.tail">
[MERGE FILES]
VCF-SOURCE-CHM
</xsl:param>

</xsl:stylesheet>
