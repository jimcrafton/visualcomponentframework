<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	        version="1.0">
 
 <!--
 this uses a local path - may need to be modified for others
 -->

	<xsl:import href="D:/docbook-xsl-1.60.1/htmlhelp/htmlhelp.xsl"/>
	
	<xsl:param name="generate.legalnotice.link" select="1"/>
	<xsl:param name="html.stylesheet" select="'vcf.css'"/>
	<xsl:param name="suppress.navigation" select="0"/>
	<xsl:param name="admon.graphics" select="1"/>
	<xsl:param name="admon.graphics.path">gfx/</xsl:param>
	<xsl:param name="htmlhelp.chm" select="'xmake_docs.chm'"/>
	
	<xsl:param name="htmlhelp.hhc.binary" select="0"/>
	<xsl:param name="htmlhelp.hhc.folders.instead.books" select="0"/>

	<xsl:param name="toc.section.depth" select="4"/>
	<xsl:param name="generate.section.toc.level" select="1"/>
	<xsl:param name="section.autolabel" select="1"/>
	<xsl:param name="section.label.includes.component.label" select="1"/>

	<xsl:param name="htmlhelp.hhc.generate.source.chm.link" select="0"/>




<!--
<xsl:param name="htmlhelp.hhp.tail">
<xsl:if test="$htmlhelp.hhc.generate.source.chm.link != 0">
[MERGE FILES]
VCF-SOURCE-CHM
</xsl:if>
</xsl:param>
-->



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

</xsl:stylesheet>
