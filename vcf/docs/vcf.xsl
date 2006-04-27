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

-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	        version="1.0">
 
 
 <!--
 this uses a local path - may need to be modified for others
 --> 
	<xsl:import href="f:/code/docbook-xsl-1.69.1/htmlhelp/htmlhelp.xsl"/>
	
	<xsl:param name="generate.legalnotice.link" select="1"/>
	<xsl:param name="html.stylesheet" select="'vcf.css'"/>
	<xsl:param name="suppress.navigation" select="0"/>
	<xsl:param name="admon.graphics" select="1"/>
	<xsl:param name="admon.graphics.path">gfx/</xsl:param>
	<xsl:param name="htmlhelp.chm" select="'vcf-docbook.chm'"/>
	
	<xsl:param name="htmlhelp.hhc.binary" select="1"/>
	<xsl:param name="htmlhelp.chi.create" select="1"/>
	<xsl:param name="htmlhelp.hhc.folders.instead.books" select="0"/>

	<xsl:param name="toc.section.depth" select="2"/>
	<xsl:param name="generate.section.toc.level" select="5"/>	
	<xsl:param name="section.autolabel" select="1"/>
	<xsl:param name="section.label.includes.component.label" select="1"/>

	<xsl:param name="htmlhelp.hhc.generate.source.chm.link" select="0"/>
	<xsl:param name="htmlhelp.hhp" select="'vcf-docbook.hhp'"></xsl:param>
	
	<xsl:param name="htmlhelp.hhp.window" select="'main'"></xsl:param>
	<xsl:param name="htmlhelp.show.menu" select="1"></xsl:param>
	<xsl:param name="htmlhelp.show.advanced.search" select="0"></xsl:param>
	<xsl:param name="htmlhelp.show.favorities" select="1"></xsl:param>
	<xsl:param name="htmlhelp.show.toolbar.text" select="1"></xsl:param>
	<xsl:param name="htmlhelp.remember.window.position" select="1"></xsl:param>




<xsl:param name="htmlhelp.hhp.tail">
<xsl:if test="$htmlhelp.hhc.generate.source.chm.link != 0">
[MERGE FILES]
VCF-SOURCE-CHM
</xsl:if>
</xsl:param>





<xsl:template name="hhp-main">
<xsl:variable name="default.topic">
  <xsl:choose>
    <xsl:when test="$htmlhelp.default.topic != ''">
      <xsl:value-of select="$htmlhelp.default.topic"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:call-template name="make-relative-filename">
        <xsl:with-param name="base.dir" select="$base.dir"/>
        <xsl:with-param name="base.name">
          <xsl:choose>
            <xsl:when test="$rootid != ''">
              <xsl:apply-templates select="key('id',$rootid)" mode="chunk-filename"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:apply-templates select="/" mode="chunk-filename"/>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:otherwise>
  </xsl:choose>
</xsl:variable>
<xsl:variable name="xnavigation">
  <xsl:text>0x</xsl:text>
  <xsl:call-template name="toHex">
    <xsl:with-param name="n" select="9504 + $htmlhelp.show.menu * 65536
                                          + $htmlhelp.show.advanced.search * 131072
                                          + $htmlhelp.show.favorities * 4096
                                          + (1 - $htmlhelp.show.toolbar.text) * 64
                                          + $htmlhelp.remember.window.position * 262144"/>
  </xsl:call-template>
</xsl:variable>
<xsl:variable name="xbuttons">
  <xsl:text>0x</xsl:text>
  <xsl:call-template name="toHex">
    <xsl:with-param name="n" select="0 + $htmlhelp.button.hideshow * 2
                                       + $htmlhelp.button.back * 4
                                       + $htmlhelp.button.forward * 8
                                       + $htmlhelp.button.stop * 16
                                       + $htmlhelp.button.refresh * 32
                                       + $htmlhelp.button.home * 64
                                       + $htmlhelp.button.options * 4096
                                       + $htmlhelp.button.print * 8192
                                       + $htmlhelp.button.locate * 2048
                                       + $htmlhelp.button.jump1 * 262144
                                       + $htmlhelp.button.jump2 * 524288
                                       + $htmlhelp.button.next * 2097152
                                       + $htmlhelp.button.prev * 4194304
                                       + $htmlhelp.button.zoom * 1048576"/>
  </xsl:call-template>
</xsl:variable>
<xsl:text>[OPTIONS]
</xsl:text>
<xsl:if test="$generate.index">
<xsl:text>Auto Index=Yes
</xsl:text></xsl:if>
<xsl:if test="$htmlhelp.hhc.binary != 0">
<xsl:text>Binary TOC=Yes
</xsl:text></xsl:if>
<xsl:text>Compatibility=1.1 or later
Compiled file=</xsl:text><xsl:value-of select="$htmlhelp.chm"/><xsl:text>
Contents file=</xsl:text><xsl:value-of select="$htmlhelp.hhc"/><xsl:text>
</xsl:text>
<xsl:if test="$htmlhelp.chi.create">
<xsl:text>Create CHI file=YES
</xsl:text></xsl:if>
<xsl:if test="$htmlhelp.hhp.window != ''">
<xsl:text>Default Window=</xsl:text><xsl:value-of select="$htmlhelp.hhp.window"/><xsl:text>
</xsl:text></xsl:if>
<xsl:text>Default topic=</xsl:text><xsl:value-of select="$default.topic"/>
<xsl:text>
Display compile progress=Yes
Full-text search=Yes
</xsl:text>
<xsl:if test="$generate.index">
<xsl:text>Index file=</xsl:text><xsl:value-of select="$htmlhelp.hhk"/><xsl:text>
</xsl:text></xsl:if>
<xsl:text>Language=</xsl:text>
<xsl:if test="//@lang">
  <xsl:variable name="lang" select="//@lang[1]"/>
  <xsl:value-of select="document('langcodes.xml')//gentext[@lang=string($lang)]"/>
</xsl:if>
<xsl:if test="not(//@lang)">
  <xsl:text>0x0409 English (United States)</xsl:text>
</xsl:if>
<xsl:text>
Title=</xsl:text>
  <xsl:choose>
    <xsl:when test="$htmlhelp.title = ''">
      <xsl:choose>
        <xsl:when test="$rootid != ''">
          <xsl:apply-templates select="key('id',$rootid)" mode="title.markup"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:apply-templates select="/*" mode="title.markup"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$htmlhelp.title"/>
    </xsl:otherwise>
  </xsl:choose>

<xsl:if test="$htmlhelp.hhp.window != ''">
  <xsl:text>

[WINDOWS]
</xsl:text>
<xsl:value-of select="$htmlhelp.hhp.window"/>
<xsl:text>=,"</xsl:text><xsl:value-of select="$htmlhelp.hhc"/>
<xsl:text>",</xsl:text>
<xsl:if test="$generate.index">
  <xsl:text>"</xsl:text>
  <xsl:value-of select="$htmlhelp.hhk"/>
  <xsl:text>"</xsl:text>
</xsl:if>
<xsl:text>,"</xsl:text>
<xsl:value-of select="$default.topic"/>
<xsl:text>",</xsl:text>
<xsl:text>"</xsl:text>
<xsl:choose>
  <xsl:when test="$htmlhelp.button.home != 0">
    <xsl:value-of select="$htmlhelp.button.home.url"/>
  </xsl:when>
  <xsl:otherwise>
    <xsl:value-of select="$default.topic"/>
  </xsl:otherwise>
</xsl:choose>
<xsl:text>"</xsl:text>
<xsl:text>,</xsl:text>
<xsl:if test="$htmlhelp.button.jump1 != 0">
  <xsl:text>"</xsl:text>
  <xsl:value-of select="$htmlhelp.button.jump1.url"/>
  <xsl:text>"</xsl:text>
</xsl:if>
<xsl:text>,</xsl:text>
<xsl:if test="$htmlhelp.button.jump1 != 0">
  <xsl:text>"</xsl:text>
  <xsl:value-of select="$htmlhelp.button.jump1.title"/>
  <xsl:text>"</xsl:text>
</xsl:if>
<xsl:text>,</xsl:text>
<xsl:if test="$htmlhelp.button.jump2 != 0">
  <xsl:text>"</xsl:text>
  <xsl:value-of select="$htmlhelp.button.jump2.url"/>
  <xsl:text>"</xsl:text>
</xsl:if>
<xsl:text>,</xsl:text>
<xsl:if test="$htmlhelp.button.jump2 != 0">
  <xsl:text>"</xsl:text>
  <xsl:value-of select="$htmlhelp.button.jump2.title"/>
  <xsl:text>"</xsl:text>
</xsl:if>
<xsl:text>,</xsl:text>
<xsl:value-of select="$xnavigation"/>
<xsl:text>,,</xsl:text>
<xsl:value-of select="$xbuttons"/>
<xsl:text>,,,,,,,,0
</xsl:text>
</xsl:if>

<xsl:text>

[FILES]
</xsl:text>

<xsl:choose>
  <xsl:when test="$rootid != ''">
    <xsl:apply-templates select="key('id',$rootid)" mode="enumerate-files"/>
  </xsl:when>
  <xsl:otherwise>
    <xsl:apply-templates select="/" mode="enumerate-files"/>
  </xsl:otherwise>
</xsl:choose>

<xsl:if test="$htmlhelp.enumerate.images">
  <xsl:variable name="imagelist">
    <xsl:choose>
      <xsl:when test="$rootid != ''">
        <xsl:apply-templates select="key('id',$rootid)" mode="enumerate-images"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:apply-templates select="/" mode="enumerate-images"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:variable>
  <xsl:choose>
    <xsl:when test="function-available('exsl:node-set') and function-available('set:distinct')">
      <xsl:for-each select="set:distinct(exsl:node-set($imagelist)/filename)">
        <xsl:value-of select="."/>
        <xsl:text>&#10;</xsl:text>
      </xsl:for-each>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$imagelist"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:if>

<xsl:if test="($htmlhelp.force.map.and.alias != 0) or 
              ($rootid = '' and //processing-instruction('dbhh')) or
              ($rootid != '' and key('id',$rootid)//processing-instruction('dbhh'))">
  <xsl:text>
[ALIAS]
#include </xsl:text><xsl:value-of select="$htmlhelp.alias.file"/><xsl:text>

[MAP]
#include </xsl:text><xsl:value-of select="$htmlhelp.map.file"/><xsl:text>
</xsl:text>
</xsl:if>

<xsl:value-of select="$htmlhelp.hhp.tail"/>
</xsl:template>





<!--
This template is used to create the hhc file. 
If the htmlhelp.hhc.generate.source.chm.link  is enabled then
we'll add anothe toc entry at the end which will link to the
file specifed in VCF-SOURCE-CHM file. the VCF-SOURCE-CHM word
will be replaced by a sed script in tyhe makefile 
-->

<xsl:template name="hhc-main">
  <xsl:text disable-output-escaping="yes">&lt;HTML&gt;
&lt;HEAD&gt;
&lt;/HEAD&gt;
  &lt;BODY&gt;
</xsl:text>
  <xsl:if test="$htmlhelp.hhc.folders.instead.books != 0">
    <xsl:text disable-output-escaping="yes">&lt;OBJECT type="text/site properties"&gt;
	&lt;param name="ImageType" value="Folder"&gt;
&lt;/OBJECT&gt;
</xsl:text>
  </xsl:if>
  <xsl:if test="$htmlhelp.hhc.show.root != 0">
<xsl:text disable-output-escaping="yes">&lt;UL&gt;
</xsl:text>
  </xsl:if>

  <xsl:choose>
    <xsl:when test="$rootid != ''">
      <xsl:apply-templates select="key('id',$rootid)" mode="hhc"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:apply-templates select="/" mode="hhc"/>
    </xsl:otherwise>
  </xsl:choose>

<xsl:if test="$htmlhelp.hhc.generate.source.chm.link != 0">
<xsl:text disable-output-escaping="yes">
	&lt;LI&gt; &lt;OBJECT type="text/sitemap"&gt;
		&lt;param name="Name" value="Source Documentation"&gt;
		&lt;/OBJECT&gt;
		&lt;OBJECT type="text/sitemap"&gt;
			&lt;param name="Merge" value="VCF-SOURCE-CHM::\index.hhc"&gt;
			&lt;/OBJECT&gt;
</xsl:text>
</xsl:if>

  <xsl:if test="$htmlhelp.hhc.show.root != 0">
  <xsl:text disable-output-escaping="yes">&lt;/UL&gt;
</xsl:text>
  </xsl:if>
  <xsl:text disable-output-escaping="yes">&lt;/BODY&gt;
&lt;/HTML&gt;</xsl:text>
</xsl:template>


	<!-- 
	What follows are the header and footer customizations for the vcf docbook
	-->	
	<!--
	<xsl:template name="user.header.navigation">	
	<![CDATA[	

	]]>
	</xsl:template>
	-->
	
	<!--
	<xsl:template name="user.footer.navigation">	
	<![CDATA[
		
	]]>	 
	</xsl:template>
-->

<xsl:template name="chunk-element-content">
  <xsl:param name="prev"/>
  <xsl:param name="next"/>
  <xsl:param name="nav.context"/>
  <xsl:param name="content">
    <xsl:apply-imports/>
  </xsl:param>

  <html>
    <xsl:call-template name="html.head">
      <xsl:with-param name="prev" select="$prev"/>
      <xsl:with-param name="next" select="$next"/>
    </xsl:call-template>

    <body>
      <xsl:call-template name="body.attributes"/>

<!-- header with VCF and SF logo -->
<table width="100%" border="0" cellpadding="0" cellspacing="0">
 <tr>
  <td class="logoCell" width="400" height="80" valign="top">
   <table width="400" border="0" cellpadding="0" cellspacing="0">
    <tr>
     <td width="400" height="80" align="center" valign="middle"><a name="top"></a>
	 <img alt="" border="0" src="gfx/logo.png"/></td>
    </tr>
   </table>
  </td>
  <td class="logoCell" width="100%" valign="top">
   <table width="100%" border="0" cellpadding="0" cellspacing="0">
    <tr>
     <td width="100%" height="80" valign="top">&#160;</td>
    </tr>
   </table>
  </td>
  <td class="logoCell" width="350" valign="top">
   <table width="350" border="0" cellpadding="0" cellspacing="0">
    <tr>
     <td width="350" height="80" align="center" valign="middle">
      <a href="http://sourceforge.net/projects/vcf/" target="_blank">
       <img alt="Sourceforge.net - The VCF's Project Host" border="0" src="gfx/sflogo.png"/>
      </a>
     </td>
    </tr>
   </table>
  </td>
 </tr>
</table>

<!-- header with web links, below VCF and SF logo -->
<table width="100%" border="0" cellpadding="0" cellspacing="0">
 <tr>
  <td class="topCell" width="100%" height="20" align="right" valign="middle">
   &#160;&#160;
   <a class="topLink" href="http://vcf-online.org/index.php">The VCF Website Home</a>
   &#160;&#160;|&#160;&#160;
   <a class="topLink" href="http://vcf-online.org/forums/">Online Discussion Forums</a>
   &#160;&#160;|&#160;&#160;	
   <a class="topLink" href="http://sourceforge.net/projects/vcf/">Sourceforge.net Project Page</a>
   &#160;&#160;
  </td>
 </tr>
</table>

<!-- Navigation must be in table or MS HTML Help will screw it -->
<table align="center" width="95%" border="0" cellpadding="0" cellspacing="0">
  <tr><td width="100%" height="1" valign="top">

      <xsl:call-template name="user.header.navigation"/>
      <xsl:call-template name="header.navigation">
        <xsl:with-param name="prev" select="$prev"/>
        <xsl:with-param name="next" select="$next"/>
        <xsl:with-param name="nav.context" select="$nav.context"/>
      </xsl:call-template>

  </td></tr>
</table>

  <!-- put main page content in here, set styles in vcf.css -->
  <div class="mainContent" >
      <xsl:call-template name="user.header.content"/>
      <xsl:copy-of select="$content"/>
      <xsl:call-template name="user.footer.content"/>
  </div>

<table width="100%" border="0" cellpadding="0" cellspacing="0">
 <tr>
  <td class="footerCell" width="100%" height="1" align="center" valign="middle">
   &#160;&#160;
   <a class="footerLink" href="http://vcf-online.org/?q=node/14">Comments or Suggestions?</a>   
   &#160;&#160;
   <a class="footerLink" href="http://vcf-online.org/?q=node/4">License Information</a>
   &#160;&#160;
  </td>
 </tr>
</table>

<!-- Navigation must be in table or MS HTML Help will screw it -->
<table align="center" width="98%" border="0" cellpadding="0" cellspacing="0">
  <tr><td width="100%" height="1" valign="top">
      <xsl:call-template name="footer.navigation">
        <xsl:with-param name="prev" select="$prev"/>
        <xsl:with-param name="next" select="$next"/>
        <xsl:with-param name="nav.context" select="$nav.context"/>
      </xsl:call-template>
      <xsl:call-template name="user.footer.navigation"/>
  </td></tr>
</table>

    </body>
  </html>
</xsl:template>


</xsl:stylesheet>

<!--
$Id$
-->
