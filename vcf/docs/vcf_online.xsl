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
Revision 1.4  2003/12/18 05:15:52  ddiego
merge from devmain-0-6-2 branch into the stable branch

Revision 1.3.2.1  2003/12/08 05:05:27  ddiego
added a bunch more documentation to classes, and added support for new doc
keywords (@delegates, @del, @delegate, @event, and @eventtype). This
makes it easier to see at a glance what events a class fires off.
Added finishing touches for the Action implementation and have a partially
complete example for this checked in.

Revision 1.3  2003/08/09 21:01:40  ddiego
minor changes to doc makefile

Revision 1.2  2003/05/17 20:36:55  ddiego
this is the checkin for the 0.6.1 release - represents the merge over from
the devmain-0-6-0 branch plus a few minor bug fixes

Revision 1.1.2.1  2003/03/10 03:58:34  ddiego
fixes ot better support online html, plus the addition of a little C++
program to stip stuff

Revision 1.1.2.4  2003/03/07 04:33:02  ddiego
added more docs for appkit. made some mods to the vcf.xsl stylesheet
to turn on section numbering

Revision 1.1.2.3  2003/03/04 04:53:51  ddiego
filled some docs

Revision 1.1.2.2  2003/03/03 22:42:41  ddiego
stuff

Revision 1.1.2.1  2003/03/03 03:39:49  ddiego
initial check-in of docbook vcf documentation, plus neccesary stylsheets
and images

-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	        version="1.0">
 
 <!--
 this uses a local path - may need to be modified for others
 -->
	<xsl:import href="vcf.xsl"/>
	
	<xsl:param name="generate.legalnotice.link" select="1"/>
	<xsl:param name="html.stylesheet" select="'vcf.css'"/>
	<xsl:param name="suppress.navigation" select="0"/>
	<xsl:param name="admon.graphics" select="1"/>
	<xsl:param name="admon.graphics.path">gfx/</xsl:param>
	<xsl:param name="htmlhelp.chm" select="'vcf_docs.chm'"/>
	
	<xsl:param name="toc.section.depth" select="4"/>
	<xsl:param name="generate.section.toc.level" select="1"/>
	<xsl:param name="section.autolabel" select="1"/>
	<xsl:param name="section.label.includes.component.label" select="1"/>


	<xsl:param name="html.ext"	select="'.html'"/>
	
	
	<!--
	<xsl:template match="legalnotice" mode="titlepage.mode">
	  <xsl:variable name="id"><xsl:call-template name="object.id"/></xsl:variable>
	  <xsl:choose>
	    <xsl:when test="$generate.legalnotice.link != 0">
	      <xsl:variable name="filename">
		<xsl:call-template name="make-relative-filename">
		  <xsl:with-param name="base.dir" select="$base.dir"/>
		  <xsl:with-param name="base.name" select="concat('ln-',$id,$html.ext)"/>
		</xsl:call-template>
	      </xsl:variable>
	
	      <xsl:variable name="title">
		<xsl:apply-templates select="." mode="title.markup"/>
	      </xsl:variable>
	
	      <a href="{concat('ref.php?src=ln-',$id,$html.ext)}">
		<xsl:copy-of select="$title"/>
	      </a>
	
	      <xsl:call-template name="write.chunk">
		<xsl:with-param name="filename" select="$filename"/>
		<xsl:with-param name="quiet" select="$chunk.quietly"/>
		<xsl:with-param name="content">
		 <html>
		    <head>		    
		      <xsl:call-template name="system.head.content"/>
		      <xsl:call-template name="head.content"/>
		      <xsl:call-template name="user.head.content"/>
		    </head>
		    <body>
		      <xsl:call-template name="body.attributes"/>
		      <div class="{local-name(.)}">
			<xsl:apply-templates mode="titlepage.mode"/>
		      </div>
		    </body>
		  </html>
		</xsl:with-param>
	      </xsl:call-template>
	    </xsl:when>
	    <xsl:otherwise>
	      <div class="{local-name(.)}">
		<xsl:apply-templates mode="titlepage.mode"/>
	      </div>
	    </xsl:otherwise>
	  </xsl:choose>
	</xsl:template>	
	-->
<!--
	<xsl:template name="href.target">
		<xsl:text>ref.php?src=</xsl:text>
		<xsl:param name="object" select="."/>
		<xsl:variable name="ischunk">
			<xsl:call-template name="chunk">
				<xsl:with-param name="node" select="$object"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:apply-templates mode="chunk-filename" select="$object"/>
	
		<xsl:if test="$ischunk='0'">
			<xsl:text>#</xsl:text>
			<xsl:call-template name="object.id">
				<xsl:with-param name="object" select="$object"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>
-->


</xsl:stylesheet>
