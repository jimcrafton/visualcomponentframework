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
import time # wait
import re
from copy import copy # to copy(Option.TYPE_CHECKER)
from optparse import OptionParser, Option, OptionValueError
import commands # for uuidgen

# for isUnixOs
_names = sys.builtin_module_names

modules ={}


# globals
compilerVc6  = 'vc6'
compilerVc70 = 'vc70'
compilerVc71 = 'vc71'
compilerIcl7 = 'icl7'
compilerVersionVc6 = 600
compilerVersionVc70 = 700
compilerVersionVc71 = 710

g_default_config = "reformatVc.ini"
g_default_section = "vcfscript"
g_default_allProjects = './build/vc60/vcfAllProjects.dsw'
g_default_allExamples = './Examples/Examples.dsw'
g_dependencyFilterExamplesProject = 'examples/'
#g_referenceSolution = './build/vc70/vcfAllProjects_vc70.sln'
g_subdir_examples = 'examples/' # dir where we know we have just examples, i.e. simple executable files

# ( hardcoded )
g_tableFilterWorkspacesCreation = {}
g_tableFilterWorkspacesCreation[ 'vcfallprojects' ] = './'
g_tableFilterWorkspacesCreation[ 'examples' ] = 'examples/'

# ( hardcoded )
g_gtkLibrariesList = [ 'GraphicsKitGtk', 'ApplicationKitGtk' ] # Remark: this list must follow an increasing dependency order

g_filenameLog = 'reformatVc.log'

extDsp = '.dsp'
extWsp = '.dsw'
extVcproj = '.vcproj'
extSln = '.sln'


# this is hardcoded: expecially the sln files heed the non unix stye for the path
#app.options.unixStyle = False
g_internal_unixStyle = True  # IMPORTANT: use True otherwise it will not work under cygwin !
g_uuidVisualStudio = '8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942' # the same everywhere: if this is wrong it will complain for all projects not installed
g_options_showNamesForUuids = False # Use False. This breaks the solution file, but it shows the names. When put it back to False it fixes the files corrupted when it was set to True!
g_workspaceHasPrecedenceOverSolution = True # use True so changes in the workspaces will be reflected into the dependency changes in the solutions
testingParse = False #%%%
g_printFilterGroupTrees = False
addEntriesForVc71WhenSynchToVc70 = False # this will alter the configuration information contained in the vcproj. Better False
addToolsForVc71WhenSynchToVc70   = False # this will alter the configuration information contained in the vcproj. Better False
g_uses_FileConfiguration_infos_from_original_file = True # IMPORTANT: keep this True otherwise you loos all the per-file information specific of vc70 and vc71 and unknown to vc6
g_debugFileList = [ '' ] # [ 'xmake', 'vcfAllLibs' ] [ 'Examples.dsw', 'vcfAllProjects.dsw' ] [ 'win32htmlbrowser_staticlib' ] [ 'docbookarticle_vc70.vcproj' ] [ 'vcmcvs_vc71.vcproj' ] [ 'js' ] [ 'docbookarticle' ] [ 'defaultxmldoc_vc70' ] [ 'freeimagelib' ] [ 'msdnintegrator' ] [ 'localization' ]   ( see isFileIn2() )
g_include_vcproj_in_changed_files_counted = True # this includes the vcproj files created/changed in the total count of changed files
g_keepFirstDot_standard = 4 # === g_keepFirstDot_StandardVc # standard format for paths in projects files has ./ at the beginning
g_fix_last_slash_in_path = True # True only when we need to fix it. Then put it back
g_sort_workspace_ignorecase = False # use True: the projects in a workspace are sorted by not ignoring the case by VisualStudio

# vc7 always put '/' at the end of a directory name when it creates one project file,
# but custom build cannot copy any file into a path like that !
# so not any variable like $(InputPath) or $(OutDir) can have that format !
g_dir_final_separator = '\\'

# under win32 I am forced to get the uuid from a table because the uuid algorithms on win32 are pretty bad
# this ends up in having a limited number of uuid which can cause problems
# so it is suggested use this script under win32 only when debugging, even if I can say
# that it is working right also under win32 with the uuids table
g_disableUuidgen_on_win32 = False





# Some macros used internally for clarity
g_KeepFirstDot_False = False
g_KeepFirstDot_True = 1
g_KeepFirstDot_Add  = 2       # add './' at the beginning anyway
g_KeepFirstDot_AddOnlyIfNoDots = 3 # add './' at the beginning only if it is not already like: '../'
g_keepFirstDot_StandardVc = 4 # like 3 but it also remove the './' if it exists

g_MinPathIsDot_False = False
g_MinPathIsDot_True  = True

g_IsDirForSure_False = 0
g_IsDirForSure_True  = 1
g_IsDirForSure_ChkDot = 2  # check automatically if the path is a directory or not according with if it has a dot or not
#                           # There is an option in vc70: 'ObjectFile=".\vc70\DebugDLL/" that *WANTS* the '/' at the end if it is not a file otherwise it
#                           # compiles only in a 'partial' and weird way: because ObjectFile expect the value to be a file (and accept a dir if we have a [back]slash at the end)


#enum AppType
# we use same values as VisualStudio 7
#typeUnknown        0
#typeApplication    1
#typeDynamicLibrary 2
#typeStaticLibrary  4
#typeGeneric        10
enumAppTypeNone    = -1
enumAppTypeUnknown = 0
enumAppTypeExe     = 1
enumAppTypeDll     = 2
enumAppTypeLib     = 4
enumAppTypeGeneric = 10


enum_ADD_NONE        = 0
enum_ADD_CPP         = 1
enum_SUBTRACT_CPP    = 2
enum_ADD_LINK32      = 3
enum_SUBTRACT_LINK32 = 4
enum_ADD_LIB32       = 5
enum_SUBTRACT_LIB32  = 6
enum_ADD_BSC32       = 7

#enumStatic  = { 'static' : 1, 'dynamic' : 2 }

re_find_one_of_non_path_char   = re.compile( r'[$;,;]+' )

re_trueproject = re.compile( r'# Microsoft Developer Studio Project File - Name="(?P<trueProjectName>[a-zA-Z0-9_\- \\/.]*?)" - Package Owner=<([0-9]+)>' )
re_output_or_intermed_dir   = re.compile( r'(^# PROP (Output|Intermediate)_Dir "(?P<subdir>[a-zA-Z0-9_\- $\(\)\\/.]*?)")' )
re_output_dir               = re.compile( r'^# PROP Output_Dir "(?P<subdir>[a-zA-Z0-9_\- $\(\)\\/.]*?)"' )
re_intermed_dir             = re.compile( r'^# PROP Intermediate_Dir "(?P<subdir>[a-zA-Z0-9_\- $\(\)\\/.]*?)"' )
re_targettype           = re.compile( r'# TARGTYPE "(?P<platform>\w+) \((?P<platformNum>\w+)\) (?P<projectType>[a-zA-Z0-9_\- ]+?)" (?P<code>\w+)' )
#re_configurationOld        = re.compile( r'!(ELSE)?IF  "\$\(CFG\)"\s+==\s+"(?P<projectName>\w+)\s+-\s+(?P<platform>\w+)\s+(?P<configFullName>(\w+\s*)+)"' )
re_configuration        = re.compile( r'!(ELSE)?IF  "\$\(CFG\)"\s+==\s+"(?P<projectName>\w+)\s*?-\s*?(?P<platform>\w+)\s+(?P<configFullName>[a-zA-Z0-9_\- $\(\)\\/.]*)"' )
#re_confignamesplitOld      = re.compile( r'((\w+)\s+)*(?P<configName>\w+)' )
re_confignamesplit      = re.compile( r'((\w+)\s+)+?(?P<configName>[a-zA-Z0-9 _\- $\(\)\\/.]*)' ) # the first word and take all the others
re_configuration_endif  = re.compile( r'!ENDIF\s*?$' )
re_dsp_custom_build_basic_beg   = re.compile( r'# Begin Custom Build' )
re_dsp_custom_build_basic_end   = re.compile( r'# End Custom Build' )
re_dsp_custom_build_basic_lib   = re.compile( r'\s*?lib\s+?' ) # lib command
re_dsp_custom_build_basic_dll   = re.compile( r'\s*?/dll\s+?' ) # /dll option in a (link ?) command

re_dsp_group_name_basic = re.compile( r'# Name' )
re_dsp_group_name       = re.compile( r'# Name "(?P<projectName>\w+) - (?P<platform>\w+) (?P<configName>[a-zA-Z0-9_\- $\(\)\\/.]*)"' )
re_dsp_group_basic_beg  = re.compile( r'# Begin Group' )
re_dsp_group            = re.compile( r'# Begin Group "(?P<groupname>[a-zA-Z0-9_\- $\(\)\\/.]*?)"' )
re_dsp_group_basic_end  = re.compile( r'# End Group' )
re_dsp_filter_basic     = re.compile( r'# PROP Default_Filter' )
re_dsp_filter           = re.compile( r'# PROP Default_Filter "(?P<filtervalue>[a-zA-Z0-9_;,\-\* $\(\)\\/.]*?)"' )
re_dsp_src_file_beg     = re.compile( r'# Begin Source File' )
re_dsp_src_file_end     = re.compile( r'# End Source File' )
re_dsp_source_basic     = re.compile( r'SOURCE=' )
re_dsp_source           = re.compile( r'SOURCE="?(?P<sourcename>[a-zA-Z0-9_\- $\(\)\\/.]*)"?' ) # note: 1) no *? 2) wihout r'' the \" should be written as " only ! otherwise it stops at the first '\'
re_dsp_useprecompheader_c = re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]*?)"?' )
re_dsp_useprecompheader_u = re.compile( r'/Yu"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]*?)"?' )


# Note:
# if we have:
# ADD CPP /Yc"vcf/ApplicationKit/ApplicationKit.h"
#re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]+?)"?' ) match '/Yc"v'
#re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]*?)"?' ) match '/Yc"'
#re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]+)"?' )  match '/Yc"vcf/ApplicationKit/ApplicationKit.h"'
#re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]*)"?' )  match '/Yc"vcf/ApplicationKit/ApplicationKit.h"'
#re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]+?)"' )  match '/Yc"vcf/ApplicationKit/ApplicationKit.h"'
#re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]*?)"' )  match '/Yc"vcf/ApplicationKit/ApplicationKit.h"'
#re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]+)"' )   match '/Yc"vcf/ApplicationKit/ApplicationKit.h"'
#re.compile( r'/Yc"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]*)"' )   match '/Yc"vcf/ApplicationKit/ApplicationKit.h"'
# if we have:
# ADD CPP /Yu something
#re.compile( r'/Yu"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]+?)"?' ) match '/Yu '
#re.compile( r'/Yu"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]*?)"?' ) match '/Yu'
#re.compile( r'/Yu"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]+)"?' )  match '/Yu something'
#re.compile( r'/Yu"?(?P<precompheader>[a-zA-Z0-9_\- $\(\)\\/.]*)"?' )  match '/Yu something'


re_vcp_general_version_xml              = re.compile( r'\s*?<\?xml version\s*=\s*"(?P<version_xml>[a-zA-Z0-9\.]+)"\s*encoding\s*=\s*"(?P<encoding_xml>[a-zA-Z0-9_;,\- $\(\)\\/.]+)"\?>' )
re_vcp_general_visualStudioProject_beg  = re.compile( r'\s*?<VisualStudioProject$' )
re_vcp_general_visualStudioProject_end  = re.compile( r'\s*?</VisualStudioProject>' )
re_vcp_general_projectType              = re.compile( r'\s*?ProjectType="(?P<projectType>[a-zA-Z0-9_;,\-\+ $\(\)\\/.]*?)"' )
#re_vcp_keyname               = re.compile( r'\s*?Name="(?P<keyname>[a-zA-Z0-9_;,\-\* $\(\)\\|/.]*?)"' )
re_vcp_general_version_vc_project       = re.compile( r'\s*?Version="(?P<version_vc_project>[a-zA-Z0-9\.]+)"' )
re_vcp_general_sccProjectName           = re.compile( r'\s*?SccProjectName="(?P<sccProjectName>[a-zA-Z0-9_;,\-\* $\(\)\\/.]*?)"' )
re_vcp_general_sccLocalPath             = re.compile( r'\s*?SccLocalPath="(?P<sccLocalPath>[a-zA-Z0-9_;,\-\* $\(\)\\/.]*?)"' )
re_vcp_general_keyword                  = re.compile( r'\s*?Keyword="(?P<keyword>[a-zA-Z0-9_;,\-\* $\(\)\\/.]*?)"' )
re_vcp_general_projectGUID              = re.compile( r'\s*?ProjectGUID="(?P<projectGUID>[a-zA-Z0-9_;,\-\* $\(\)\{\}\\/.]*?)"' )
re_vcp_general_platforms_beg            = re.compile( r'\s*?<Platforms>' )
re_vcp_general_platforms_end            = re.compile( r'\s*?</Platforms>' )
re_vcp_general_platform_beg             = re.compile( r'\s*?<Platform$' )
re_vcp_config_configurations_beg        = re.compile( r'\s*?<Configurations>' )
re_vcp_config_configurations_end        = re.compile( r'\s*?</Configurations>' )
re_vcp_config_configuration_beg         = re.compile( r'\s*?<Configuration$' )
re_vcp_config_configuration_end         = re.compile( r'\s*?</Configuration>' )

re_vcp_config_outputDirectory           = re.compile( r'\s*?OutputDirectory="(?P<outputDirectory>[a-zA-Z0-9_:;,\-\+ $\(\)\\/.]*?)"' )


#re_vcp_entry = re.compile( r'\s*?(?P<entryName>[a-zA-Z0-9]*?)="(?P<entryValue>[a-zA-Z0-9_:;,\-\+ $\(\)\\/.]*?)"' )
re_vcp_entry = re.compile( r'\s*?(?P<entryName>[a-zA-Z0-9]*?)\s*?=\s*?"(?P<entryValue>[a-zA-Z0-9_:;,\-\+\* $&\(\)\{\}\\/.]*?)"' )
re_vcp_entry_cont0 = re.compile( r'\s*?(?P<entryName>[a-zA-Z0-9]*?)\s*?=\s*?"(?P<entryValueMultiline>[a-zA-Z0-9_:;,\-\+\* $&\(\)\{\}\\/.]*)' )
re_vcp_entry_cont1 = re.compile( r'(?P<entryValueMultiline>.*)' )


re_vcp_sectionReferences_beg = re.compile( r'\s*?<References>' )
re_vcp_sectionReferences_end = re.compile( r'\s*?</References>' )
re_vcp_sectionConfig_beg     = re.compile( r'\s*?<Configurations>' )
re_vcp_sectionConfig_end     = re.compile( r'\s*?</Configurations>' )
re_vcp_sectionFiles_beg      = re.compile( r'(?P<indentFiles>\s*?)<Files>' )
re_vcp_sectionFiles_end      = re.compile( r'\s*?</Files>' )
re_vcp_sectionFilter_beg     = re.compile( r'\s*?<Filter$' )
re_vcp_sectionFilter_end     = re.compile( r'\s*?</Filter>' )
re_vcp_sectionFilter_content = re.compile( r'\s*?Filter="(?P<filtervalue>[a-zA-Z0-9_;,\-\* $\(\)\\/.]*?)"' )
re_vcp_sectionFile_beg       = re.compile( r'\s*?<File$' )
re_vcp_sectionFile_end       = re.compile( r'\s*?</File>' )
re_vcp_sectionFile_content   = re.compile( r'\s*?RelativePath="(?P<sourcename>[a-zA-Z0-9_;,\- $\(\)\\/.]*?)"' )
re_vcp_sectionTool_beg       = re.compile( r'\s*?<Tool$' )
re_vcp_sectionFileConfig_beg = re.compile( r'\s*?<FileConfiguration$' )
re_vcp_sectionFileConfig_end = re.compile( r'\s*?</FileConfiguration>' )
re_vcp_keyname               = re.compile( r'\s*?Name="(?P<keyname>[a-zA-Z0-9_;,\-\* $\(\)\\|/.]*?)"' )


re_vcp_addIncludeDir         = re.compile( r'\s*?AdditionalIncludeDirectories="(?P<includedir>[a-zA-Z0-9_;,\- $\(\)\\/.]*?)"' )
re_vcp_preprocDefin          = re.compile( r'\s*?PreprocessorDefinitions="(?P<preprocdefin>[a-zA-Z0-9_;,\- $\(\)\\/.]*?)"' )

reDswProjectEntryMin         = re.compile( r'Project:\s*?"(?P<prjName>[a-zA-Z0-9_\- ]*?)"\s*?=' )
reDswProjectEntryFull        = re.compile( r'Project:\s*?"(?P<prjName>[a-zA-Z0-9_\- ]*?)"\s*?=\s*?(?P<prjPath>"?([a-zA-Z0-9_\- \\/.]*?)"?)(?P<pkgOwnr>\s*?-\s*?Package Owner)' )

re_dsw_projectDependency_beg     = re.compile( r'\s*?Begin Project Dependency' )
re_dsw_projectDependency_entry   = re.compile( r'\s*?Project_Dep_Name (?P<projnamedep>[a-zA-Z0-9_\- $\(\)\\/.]*)' )
re_dsw_projectDependency_end     = re.compile( r'\s*?End Project Dependency' )
re_dsw_package_beg     = re.compile( r'\s*?{{{' )
re_dsw_package_end     = re.compile( r'\s*?}}}' )


re_sln_solutionFileVersion       = re.compile( r'Microsoft Visual Studio Solution File, Format Version (?P<slnVersion>[a-zA-Z0-9\.]*)' ) # no *?
re_sln_projectpath_entry         = re.compile( r'Project\("{(?P<uuidVs>[a-zA-Z0-9_\-]+)}"\) = "(?P<projname>[a-zA-Z0-9_\- $\(\)\\/.]*?)", "(?P<projPath>[a-zA-Z0-9_\- $\(\)\\/.]*?)", "{(?P<uuidProj>[a-zA-Z0-9_\-]+)}"' )
re_sln_dependency_entry          = re.compile( r'\s*?{(?P<uuidProj>[a-zA-Z0-9_\-]+)} = {(?P<uuidProj2>[a-zA-Z0-9_\-]+)}' )
re_sln_projSectionDependency_beg = re.compile( r'\s*?ProjectSection\(ProjectDependencies\) = postProject' )
re_sln_project_end               = re.compile( r'EndProject$' )

re_sln_globals_beg                      = re.compile( r'Global$' )
re_sln_globalSection_beg                = re.compile( r'\s*?GlobalSection\((?P<sectionName>[a-zA-Z0-9_\-]+)\)\s*?=\s*?(?P<prepostSolution>[a-zA-Z0-9_\-]+)' )
re_sln_globalSectionDPCodeReview_beg    = re.compile( r'\s*?GlobalSection\(DPCodeReviewSolutionGUID\) = preSolution' )
re_sln_globalSectionDPCodeReview_entry  = re.compile( r'\s*?DPCodeReviewSolutionGUID = {(?P<uuidDPCodeReview>[a-zA-Z0-9_\-]+)}' )
re_sln_globalSectionSolConfig_beg       = re.compile( r'\s*?GlobalSection\(SolutionConfiguration\) = preSolution' )
re_sln_globalSectionSolConfig_entryVc70 = re.compile( r'\s*?ConfigName.(?P<configNum>[a-zA-Z0-9]+) = (?P<configName>[a-zA-Z0-9\- ]+)' )
re_sln_globalSectionSolConfig_entryVc71 = re.compile( r'\s*?(?P<configName>[a-zA-Z0-9\- ]+) = (?P<configName2>[a-zA-Z0-9\- ]+)' )
re_sln_globalSectionDependency_beg      = re.compile( r'\s*?GlobalSection\(ProjectDependencies\) = postSolution' )
re_sln_globalSectionDependency_entry    = re.compile( r'\s*?{(?P<uuidProj>[a-zA-Z0-9_\-]+)}.(?P<depNum>[a-zA-Z0-9]+) = {(?P<uuidProj2>[a-zA-Z0-9_\-]+)}' )
re_sln_globalSectionProjectConfig_beg   = re.compile( r'\s*?GlobalSection\(ProjectConfiguration\) = postSolution' )
re_sln_globalSectionProjectConfig_entry = re.compile( r'\s*?{(?P<uuidProj>[a-zA-Z0-9_\-]+)}.(?P<configNameExtended>[a-zA-Z0-9_\- \.]+) = (?P<configFullName>[a-zA-Z0-9_\- \.]+)\|(?P<platform>\w+)' )
re_sln_globalSectionExtensibGlobals_beg = re.compile( r'\s*?GlobalSection\(ExtensibilityGlobals\) = postSolution' )
re_sln_globalSectionExtensibAddIns_beg  = re.compile( r'\s*?GlobalSection\(ExtensibilityAddIns\) = postSolution' )
re_sln_globalSection_end                = re.compile( r'\s*?EndGlobalSection$' )
re_sln_globals_end                      = re.compile( r'\s*?EndGlobal$' )



enumSection_None                        = 0
enumSection_DPCodeReviewSolutionGUID    = 1
enumSection_SolutionConfiguration       = 2
enumSection_ProjectDependencies         = 3
enumSection_ProjectConfiguration        = 4
enumSection_ExtensibilityGlobals        = 5
enumSection_ExtensibilityAddIns         = 6
enumSection_completed                   = 9


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
re_option_out_dir_spaces    = re.compile( r'/out:"(?P<pathname>[a-zA-Z0-9_\- $\(\)\\/.]*?)"' )
re_option_out_dir_nospaces  = re.compile( r'/out:(?P<pathname>[a-zA-Z0-9_\-$\(\)\\/.]*)' )

re_custom_build_beg         = re.compile( r'^# Begin Custom Build' )
re_custom_build_end         = re.compile( r'^# End Custom Build'   )
re_custom_build_rule        = re.compile( r'^\s*?"?(?P<rule>[a-zA-Z0-9_ \-$\(\)\\/.]*)"?\s*?:' )

g_mapCompilerNameVersion = {}
g_mapCompilerNameVersion[ compilerVc6  ] = compilerVersionVc6
g_mapCompilerNameVersion[ compilerVc70 ] = compilerVersionVc70
g_mapCompilerNameVersion[ compilerVc71 ] = compilerVersionVc71
g_mapCompilerVersionName = {}
g_mapCompilerVersionName[ compilerVersionVc6  ] = compilerVc6
g_mapCompilerVersionName[ compilerVersionVc70 ] = compilerVc70
g_mapCompilerVersionName[ compilerVersionVc71 ] = compilerVc71

g_mapToolsOnlyVc71 = {}
g_mapToolsOnlyVc71[ 'VCXMLDataGeneratorTool' ] = 1
g_mapToolsOnlyVc71[ 'VCManagedWrapperGeneratorTool' ] = 1
g_mapToolsOnlyVc71[ 'VCAuxiliaryManagedWrapperGeneratorTool' ] = 1
g_vecToolNamesVc70 = [ \
    'VCCLCompilerTool', 'VCCustomBuildTool', 'VCLinkerTool', \
    'VCMIDLTool', 'VCPostBuildEventTool', 'VCPreBuildEventTool', 'VCPreLinkEventTool', \
    'VCResourceCompilerTool', 'VCWebServiceProxyGeneratorTool', \
    'VCWebDeploymentTool'
]
g_vecToolNamesVc71 = [ \
    'VCCLCompilerTool', 'VCCustomBuildTool', 'VCLinkerTool', \
    'VCMIDLTool', 'VCPostBuildEventTool', 'VCPreBuildEventTool', 'VCPreLinkEventTool', \
    'VCResourceCompilerTool', 'VCWebServiceProxyGeneratorTool', 'VCXMLDataGeneratorTool', \
    'VCWebDeploymentTool', 'VCManagedWrapperGeneratorTool', 'VCAuxiliaryManagedWrapperGeneratorTool'
]

g_mapToolEntriesOnlyVc71 = {}
g_mapToolEntriesOnlyVc71[ 'TargetMachine' ] = 'VCLinkerTool'
g_mapToolEntriesOnlyVc71[ 'HeaderFileName' ] = 'VCMIDLTool'
g_vecToolEntriesVc71 = [ \
    'TargetMachine', 'HeaderFileName' \
]

g_mapToolEntriesOnlyVc71DefaultValues = {}
g_mapToolEntriesOnlyVc71DefaultValues[ 'TargetMachine' ] = '1'
g_mapToolEntriesOnlyVc71DefaultValues[ 'HeaderFileName' ] = '' # empty but there

g_mapPathEntries = {}
g_mapPathEntries[ 'OutputDirectory'             ] = True
g_mapPathEntries[ 'IntermediateDirectory'       ] = True
g_mapPathEntries[ 'AdditionalIncludeDirectories'] = True
g_mapPathEntries[ 'PrecompiledHeaderFile'       ] = True
g_mapPathEntries[ 'AssemblerListingLocation'    ] = True
g_mapPathEntries[ 'ObjectFile'                  ] = True
g_mapPathEntries[ 'ProgramDataBaseFileName'     ] = True
#g_mapPathEntries[ 'AdditionalDependencies'     ] = True
g_mapPathEntries[ 'OutputFile'                  ] = True
g_mapPathEntries[ 'AdditionalLibraryDirectories'] = True
g_mapPathEntries[ 'ProgramDatabaseFile'         ] = True
g_mapPathEntries[ 'TypeLibraryName'             ] = True
g_mapPathEntries[ 'HeaderFileName'              ] = True


#g_mapPathEntries[ 'Name'                        ] = False
#g_mapPathEntries[ 'Optimization'                ] = False
#g_mapPathEntries[ 'AdditionalIncludeDirectories'] = True
#g_mapPathEntries[ 'PreprocessorDefinitions'     ] = False
#g_mapPathEntries[ 'BasicRuntimeChecks'          ] = False
#g_mapPathEntries[ 'RuntimeLibrary'              ] = False
#g_mapPathEntries[ 'RuntimeTypeInfo'             ] = False
#g_mapPathEntries[ 'PrecompiledHeaderFile'       ] = True
#g_mapPathEntries[ 'AssemblerListingLocation'    ] = True
#g_mapPathEntries[ 'ObjectFile'                  ] = True
#g_mapPathEntries[ 'ProgramDataBaseFileName'     ] = True
#g_mapPathEntries[ 'WarningLevel'                ] = False
#g_mapPathEntries[ 'SuppressStartupBanner'       ] = False
#g_mapPathEntries[ 'DebugInformationFormat'      ] = False
#g_mapPathEntries[ 'CompileAs'                   ] = False
#g_mapPathEntries[ 'AdditionalOptions'           ] = False
#g_mapPathEntries[ 'AdditionalDependencies'      ] = False
#g_mapPathEntries[ 'OutputFile'                  ] = True
#g_mapPathEntries[ 'LinkIncremental'             ] = False
#g_mapPathEntries[ 'SuppressStartupBanner'       ] = False
#g_mapPathEntries[ 'AdditionalLibraryDirectories'] = True
#g_mapPathEntries[ 'GenerateDebugInformation'    ] = False
#g_mapPathEntries[ 'ProgramDatabaseFile'         ] = True
#g_mapPathEntries[ 'SubSystem'                   ] = False
#g_mapPathEntries[ 'EntryPointSymbol'            ] = False
#g_mapPathEntries[ 'TargetMachine'               ] = False
#g_mapPathEntries[ 'PreprocessorDefinitions'     ] = False
#g_mapPathEntries[ 'MkTypLibCompatible'          ] = False
#g_mapPathEntries[ 'SuppressStartupBanner'       ] = False
#g_mapPathEntries[ 'TargetEnvironment'           ] = False
#g_mapPathEntries[ 'TypeLibraryName'             ] = True
#g_mapPathEntries[ 'HeaderFileName'              ] = False
#g_mapPathEntries[ 'PreprocessorDefinitions'     ] = False
#g_mapPathEntries[ 'Culture'                     ] = False






# this script uses uuidgen under linux/cygwin ( by capturing the output from uuidgen )
# under windows we uses this map in way to make sure that the same uuid is not used twice
# ( I did this so I can debug it with Boa )
# Suggestion: run this script under linux/cygwin
g_uuidList = [ \
'8d0b1cca-1c9e-4113-acb5-67d0c8eb9ffc', 'e516c5d6-7130-4d9a-a233-8dedcb777a83', 'ba3c4d90-190e-463b-9c0f-dc898b1433ed', '499594c2-7468-4696-ba67-e09fdd194d2b', '93943ede-a510-43e5-97fb-aa269e4f0c0b', \
'c59f9186-362c-4020-afec-f9f42bdd3723', 'fb6ee931-23d6-4a12-8a22-3bc354267563', 'ae86332f-2e64-460b-8363-c502de1bbfb3', '18f07694-fc61-4c07-9650-189e329972b2', '49eccc34-695d-472f-be5f-1e2fc4fdcecd', \
'505e7ae6-3414-4d22-9be7-87ec093fed53', 'b68a433e-59b4-41a2-9243-af448a3f7bad', 'b6be4f10-66ab-4bb4-b2d4-9bb5f6fc10e3', '9c900d7c-dde4-4e0f-b5de-a326c39607dc', '37828cfc-766c-4eb6-aa88-438f963055f1', \
'a0cb95d9-cdf6-4d02-bba0-eec6631fe44f', '177137b4-88bc-4398-acc0-91dc097aa54d', '298c4e5d-293b-43fc-a61f-bf33596b5637', 'bd53c24c-c67b-4b24-a05f-4a1bbe5a8094', 'b4119c21-7e30-4967-91cc-8e0b3482ea4e', \
'3d84ea17-78ff-4a20-9ab4-0a0c01702dba', 'f57a4951-0fb4-44a8-b085-0ee25c6451bf', '86b5ee3a-638c-481a-9869-4230fc112429', '1012d59e-6477-4541-9ecc-d6c295da8d9e', 'b562b243-de36-4af0-98a1-c834f2460c30', \
'5fde7645-18ab-4b91-a5a6-709e73b3d293', 'b37ff77e-b3cc-43d4-ae50-febd3865d8f2', 'e88b35e8-8f56-4b04-821e-551e06f796f8', '394527ad-1107-4e30-938f-4eda937a208a', 'bc21e3c9-58be-41d9-8dfb-165d95232b05', \
'2cba1118-6d5e-4405-9ea5-4d49129ac169', 'caa78287-6015-4ed0-9dc3-a3bbdbba1cd0', 'd5dd97a8-79ca-4521-a493-f77a1552891d', 'a0fff5f4-47e4-46fd-8cad-c4f22e0ce545', '649358fa-164a-42ca-8e2f-9054b28b5a9e', \
'ad289448-96c5-481e-ae5e-1dac66593fcc', '11f87a5e-1c98-4279-adef-5f4e4eafa657', '108bbe68-391c-4026-931d-e964b2a6d5f0', '6b9fa509-dfae-4fe1-897a-14a8c21c100d', 'd6a7a039-a854-468e-a3a1-4d9349e02c8d', \
'042d2725-eb72-45b0-96c0-901e97b46e2a', '9c994545-14fb-4a54-b5bd-9f3ec6b74ddc', '74b5d7f3-5ca6-4dba-86be-74e2ab6d16b5', '8125dc70-d816-44bd-866a-3a8a32487b8c', '1aa0114c-624b-4b68-b468-21450e3bc575', \
'5a5d1418-7276-4b48-a075-d745546899b9', '1222a5b4-4fcb-4829-b371-3a79f7c1f60b', 'c4327fce-220f-44ce-913f-94976f67d54c', '6526562b-25c4-4fbc-be95-78b698db3df2', 'd4175fea-2eab-410f-9b1f-d59f400930ce', \
'952c1ec3-a1a8-4f5c-a191-07db4011fa2d', 'adc0fb26-2c44-4d96-ab5b-80709e603666', '56983bcd-aebe-4144-add5-461eb3222b1c', 'fc6f4770-9489-42e5-a96c-e04cd475a850', '7bd28d37-9a7b-49bc-ad35-745f9eafd02d', \
'ef7e0952-7cf1-4e45-8f58-0327560dc634', 'd51a53fe-81c0-4615-aca2-afba2687e651', '90bc32f8-321b-4e39-aa9b-5e6eb2600242', '69adc0fe-ef6f-4064-b64a-a90e661585cb', '1209f0d2-b233-4e65-8af7-2c181c9b843b', \
'e749c8d5-1783-48dd-97a5-16fffc694855', '2e3fb6d7-f10e-4b17-a11c-6fc6378d1c97', 'ddd77842-b01b-4154-9209-8f8432332466', '5629470c-bb30-4d55-bba7-62ea2eb1191d', 'f7805a0e-d8f4-4b76-8569-70383cc6f85c', \
'98c21396-fbc9-40ba-a847-e26bcbe79994', '2db85331-c153-41d1-a653-275b0e2a0b4c', 'ffeac7ab-e3c6-479b-b679-bdabad3f3aa2', '8f6cf3db-fc3a-4936-8e6b-a7c6ab78423d', 'be9000b0-02e5-4768-8add-4b2177cc7988', \
'9884820a-2e0a-4266-a6cc-a13f83bb0256', '0162e66e-b8a0-4024-a6a2-f7557de4f3ef', '1b4e9cd1-3f83-48be-834c-f198b268cc0e', '7e757b5c-4ec5-4a33-8278-29eb0fa5035c', '189e3581-6c65-4f92-a529-acb38c354fb1', \
'10e89c30-9ca8-4af2-a8ea-a49c40b989e2', '332fc043-62d6-42d0-8ab9-bfc087dd9e39', '77578375-d531-4488-ab2a-6a56e0de965d', '355e743b-e4b1-4530-99d3-e93ab85060d9', '70f48013-0d78-4752-b312-070ef2bb95bb', \
'2a82503b-20fa-47e4-8567-7bf68158a077', '11afb61e-3780-4cbf-92d0-1054f42405f5', '9de96ab4-297f-4aa9-8ca6-a10cfddfc440', '4348087d-8c97-460d-b8d4-db563ae00877', '8460c7f0-c8c2-4ba2-b0bb-1b8aa29de6dc', \
'5982ee7a-8ecb-47bc-8fec-6389b9313fef', '9ea10687-408d-4fc3-ac77-0e20ef806ae6', '0581bafe-499e-4e70-84dd-1573faa756eb', '8b27425f-6d24-47b4-8ca5-d0e24536c413', 'e3fe41e9-50ec-48bc-a0b2-be87d923889c', \
'45eeec3e-9566-4ef7-a043-fad88b9b5567', '007d9b8e-1887-4f39-bd61-2a50893161e1', '0ef644a1-d579-4185-8e04-b3f95af29dc7', 'be4cce5b-e864-400c-996c-cc8d3cf3a33e', '87cb044d-9c4d-48a1-a754-63c31eb8bef8', \
'd59f5b99-8160-4344-8dfa-9c4a1de1d4f0', '7b69d174-3429-4f18-99a8-35e238c68feb', 'def80c5b-5492-4cda-8265-d649172880f3', '471607b1-ecd2-4048-8dbc-678bf124a603', '74eea0fc-e720-4aee-8627-92cd81a35ff1', \
'e8722e55-93d2-4ed1-a5c4-c045e59a2609', '182151c8-6a51-499b-b604-56918a9e18ad', '456472b5-fa41-4d9c-b4be-f7e0720574bb', '4fff2971-dd3f-458f-9d20-f6dad5a1ee9e', '675ed9eb-c153-41dc-9e7b-d3a03305be48', \
'd385a04c-f56b-4dc3-b898-23cc51c8dd62', '1f5aeb6c-bf81-4664-8071-925a8d01c676', '6eee04e1-e1f4-4b72-b480-fefeda2e9017', '772555b9-bb1b-4d8f-8f95-e4abe93f8300', '5ddc0f07-9887-46ed-b030-6df67daf619e', \
'e035df4f-8f72-4b26-b0b5-99c822dd0d20', 'c76867a6-cf04-41c6-b465-7af89272982b', 'bb206c40-d6a1-4b4b-8826-f33def1806a8', '8a1dedc5-8bee-4adf-9ece-d6675498339a', '073c0509-66b1-4646-9478-023500671a87', \
'2488257d-c488-43f4-8529-59f0bb357c66', '9ea8a29c-ee15-4aea-9c3a-212973528d40', '3d654766-acc3-424e-b92c-75dcd6554532', 'f155a370-5964-4f4a-a17d-01a4035e2ca7', '18ae3676-1f8a-4f28-9b24-7b5fc4b3afdf', \
'4d4b9f80-b90a-4151-ba10-1fe845926d26', '94556f59-ad3a-46eb-87c3-0c6d62089798', '0e154064-e640-4d10-a4cd-2620630b4f55', '1e06ec25-66b1-4aa6-b302-54bb1de7ed18', 'eb369977-8b72-4abc-a2bc-ae1c0e2c4571', \
'80eabb19-8394-4b63-83d9-c75b2710d7cc', 'f7c2af33-f05d-4b8c-a405-de474a745155', 'b7c3bdfc-1f4c-48cc-96d0-8041dd12742f', '9a8b548f-35e5-437c-9903-8de9bfb987ac', 'e45f1cef-b671-4b79-a6fa-730568314215', \
'7d445f1f-744e-4051-a84c-87a3066dd0a3', '7030b78a-1338-439b-8acf-d67ddddadafc', '04c9c334-f123-4580-8205-115a36a810bf', '5b633d51-3ba1-4efb-8a5e-21951b0c2287', 'b8c80887-6cc5-4b16-a192-31b1208d1213', \
'9d18e810-470b-4a35-ab00-ecbc8e401de8', 'b7b1ff74-4b18-4904-ab66-22268694f2de', 'ea5c6e44-8c87-4c69-91b9-647e4000b3bf', '2853fc80-2cd2-48b7-b307-db5b708dbc6a', 'a62a10ce-ccf6-4256-928e-6ba20cb4a318', \
'64044507-fc52-429f-b86c-40329d25825b', '927c1416-a603-4b48-af0f-313dfa808aac', '31c04a98-1ae5-4063-ba08-2b7dd3b236b3', '77892731-cf3a-4d45-be8b-e48279c68632', '9d221ee8-04a9-42c4-be4c-e12bad96ef18', \
'2646c2ff-a92d-429f-b2ce-2aa36df4ddf3', 'd8cd296b-4f05-4512-bd3a-eeddecffa9c9', '002e2115-f1df-4959-b16a-761d79a83f02', '92b9332d-46f6-4da5-8ef7-6e83936f86c1', '085ea6b2-5470-4341-b991-2aa088a2becb', \
'5ec943c5-a15b-4880-a183-b8900f132fb6', '642d48b5-44ce-4ac2-b77c-2fccc128b9b8', 'a1fe35a0-97d1-4748-90c6-74512a656133', 'b43717a6-df0c-42b0-b75d-c6a7e13593dc', '5a8ed1ed-6acd-47f5-99b8-b9f74fc33571', \
'99444d8b-a700-4e8e-8209-56be603bfddd', '37171744-2bbc-4346-bff5-1f04063aa78c', '933d268e-1a2d-4833-828f-c9f08ca66b0a', '9abd7cef-4bbe-4201-a620-b811fa2cc304', 'f2a6521b-f631-4d6a-8e85-f985f456a4df', \
'42eb355b-2de7-4ccc-aea5-9ced2253b1a3', 'a5e5b5df-a2dd-4796-a07c-478789ce744d', 'f531c2a1-0c5a-4ff9-93c7-b91e41816b03', '7f10a23d-4c00-401f-b4f9-e31ae82afbfd', '565b5ca9-50d9-4898-81c9-150e92f023a4', \
'7aad45bb-6cfb-44b6-8b33-c3d1bb5b935f', '246bb0c9-e7aa-4217-9cfd-5258663ab89d', '63854013-cefa-4744-870d-16c8e279e0cf', 'ff7555d6-ec7a-403f-a6cd-8dbe745579b6', '0b548377-eb4c-4624-9e27-c6e8d80d6550', \
'240ad5ae-511d-42a3-8288-5a6e90389d28', 'ec339a2a-9307-49dd-aacd-272cd1fed4e4', 'fb580117-0673-49b3-bc7b-e00f02ba02e1', '42789a98-3ef8-4a53-857f-527bda3b4b3f', '00dda250-acb3-4142-b42e-92f58da4d5af', \
'9c752445-3372-4b5b-a684-87ec69731508', '53790a34-9419-4880-91ee-f22e7b1f7455', 'ae61d667-a9a4-4551-bb4c-b1e5169b3346', '0387dbaf-62de-4c13-a7c9-e23c9b9dc6ed', 'ee456014-5e98-4f57-87a8-2e736268f5bb', \
'43f239d8-d76a-469c-b8dd-a227ac805a22', '5d9be1e8-6a87-49c8-a0e9-010572b5a704', '8bd21c9e-906f-4363-9813-e8d626de896e', 'bec75301-af6b-40e9-bf47-039cc6a71ae7', 'aa7c6349-cb28-4714-8eae-8d6dec9ce90c', \
'be561f56-1eb4-4327-bc58-9a8ba1aa919b', '5b87f9ac-f84c-4983-9318-2f8693cf8662', '1bc2da30-5a13-4cd2-8a6a-92568471482d', 'cf274a69-1788-463f-8394-bcb58f4c0e93', '1873a628-d4e0-4f91-9104-33dc96c249a5', \
'2a977a6d-d771-431b-be0c-d6595373cad1', '8e28873c-8df9-4462-a005-82e3f5c12c29', '2efeea24-74a9-4339-951d-c45faaf571f7', 'c2417fe0-1772-44bc-87ec-6dce8b999134', '2b2aa04d-e031-4c00-831a-5fb294473fe7', \
'053c5bc9-1a60-4f0a-aaa3-e6eb1d66be19', '02c522eb-9755-4e0b-9033-f835242eba4d', '8dc737c6-e4a6-4182-a319-c2fe858ad78e', 'c2458d44-6b2f-41cf-a0c9-442cad28cd84', 'dd0f39e4-9d18-4d1a-825d-aa3736922ac7', \
'49eebcd3-5768-4fd1-960c-b793156aae4f', '6ac12558-6a1d-40ea-9dc5-6dc45600925e', '89cc2765-c4e4-44c2-9ae3-f91e64f0dbc9', 'c0ec178f-16ef-4c65-8bfb-10d83bcc510c', 'd596e1e4-e321-4dda-a0fa-688f4c931505', \
'313757dd-884f-41a7-8fb1-19b016642612', '7f2a9aa3-a09a-4ce4-9c70-04ec0cf7adc6', 'cfc45f7b-0bf7-4d6b-bdb7-c2c8adbf692b', '2d2d5fdb-212a-4f31-981d-c5674658d6a4', '3020d17c-c9cf-41cd-9c1a-df903175dabf', \
'ef677eab-d4f9-4ee7-b475-bb2c30492d85', 'd1f3f182-0fe0-44ad-a55b-910ab9027b8a', '135d613a-262a-4c12-bcd0-9fd53c5db898', '8318a385-9b9f-4d22-a845-d4d0f5c26646', 'cbda6bde-33ce-4975-90af-f1f6376c8474', \
'e633c01d-97fb-4b8d-9a8d-8c105e5954fe', '34701eaa-66cf-4edb-995a-f360fb159794', 'ed2a1520-bbf6-4c14-a54e-50aa1af03118', 'a62f54ac-0b59-4db4-b507-f864a2c7b2e5', 'b1bde9a9-c9af-4b84-b39e-2555c1da5c40', \
'b982002a-cd00-4f24-8f51-877af9c13938', '0008daa3-d249-464e-8fbd-205b063c46c0', '5e10dbf1-fe1f-4ae5-9991-27dbdde51a0a', '608d9d96-f5bf-4a1d-b86d-0e0be387d796', '880ee8c4-8bc0-4e3c-8d3b-cf21689387b8', \
'6b06312b-9532-4b99-92d6-fafc16720dcb', '16019284-e525-48e6-bec0-64224d9a16f6', '8f6965e1-2105-499a-9d58-57dd7f373e99', 'f24b76ac-0344-42dd-aa0c-c8e0d4d11b4d', 'd34d9466-7af6-4aa9-921d-4744047c247c', \
'0c0a0fa4-8560-4dc7-a281-726315c4be87', 'aaabcff6-550f-4e9d-b92c-835b0d9cacea', 'a4cc420d-0bc9-4dba-aec2-91dc0e02bcb8', 'e88add20-c616-40ba-9191-a76436e88841', 'c3064370-21d3-4629-a7d2-4cd6a5df79ba', \
'307dc6eb-4b14-4775-9115-2db7e7ea43a8', '6d21a5c9-3068-41ce-96ee-8d33e1eb97c9', '1610c5d4-9c3a-40e6-91a7-2fc80889f41a', 'a0d7c003-34c5-4c4a-8bd7-aa05e7f8d6c7', '4cfd2be7-570a-4832-abf6-3c856d549f85', \
'710597c2-b274-47ce-b9f6-48adc3c19c96', '3777c5e3-3277-4a9e-966b-7bc5637e7afd', '62409d71-7426-4f79-b05c-1e53ee7e7b96', '02d7ef83-dc4b-4103-9dc0-42b42edaf757', '4bc462b5-0785-499e-82dc-9a8c19c3b42a', \
'24852f67-830c-426d-b510-8bac50912185', '9d30c68f-6a7c-400c-833d-e390cd8368f2', '063faafa-3c0a-454e-87e3-3c079cdac3f1', '087a3343-56b6-46e9-80b8-14b845dc6b9a', '381b2f65-3c7e-446d-8b07-30ed3cc7555b', \
'8f2f4c3b-c850-46dc-b18f-666e5a2c5803', '3b53736d-b120-4e52-8ffb-d05174b93d0e', '95de1a30-8957-4642-8cd7-dff32d3a6927', 'd15f83bf-8fd2-441f-a67e-d544a9515d78', 'e4dcd41d-0e00-4f73-8c33-62d975521f6b', \
'16f37f52-6b67-4f2b-9f26-d6bf2c9993c4', 'c41bb21a-c06e-4b60-ae66-5dc068eab68c', '2e3cf89a-a617-456e-9b31-1e5bd7bd4131', '3fcea333-bc11-43ec-ac5a-1e785139dc43', '07ac7fa0-23b6-4519-ac2c-61493e8efa50', \
'3f0d416e-3afa-4e6f-a461-6dc015f2e141', 'd1496002-d33f-41f8-a979-828fa5c6112b', 'e8acbe34-85f7-4289-abb4-c3aa05f22b70', '49298a37-7d89-4257-8816-7e63eb183cfd', '5097269a-066a-4813-8f0f-eb42db025252', \
'9fab5216-8598-4697-ae6e-50331a02be63', 'a1ddc57b-962c-46cb-9a23-dbaff7b89d6f', '160c52f8-0ef7-4422-b853-333d370768c1', '51055aed-6369-4c67-ae3e-a7dde56cfca7', '8da01fb0-063e-42e8-8fda-e6ea4d9c6b7a', \
'474d19ab-8de5-497e-b4df-b072935633d3', 'ad342b22-f2e2-444d-8f1b-75aee2b203d8', '935ee175-70f4-447e-91e1-52109147ce1f', 'e27986d7-18e4-4754-b7fb-593820dbea1d', '87970cdd-c7a6-4563-8172-56268414404c', \
'09bc5c54-2fad-494a-ad1f-9985e0bfc124', '8bdfbf7c-d4f9-4574-b3cd-0df57d576a65', '06b2bd55-9fe8-4aa8-80fd-f2018c6c9633', '0e591001-3ccd-4cdf-ac52-9278a5e2a432', 'd753a580-1324-4218-94fe-6df50a48165d', \
'e70280a9-55df-4f85-ba0e-e4e4ae661a96', '35969668-f9ff-45bc-a48a-c2279241b19d', 'db0b77c1-151b-485d-bf67-32be08672b6e', '4fd83aab-7090-48fb-9a73-b868f7d43389', '24f70680-6e2c-4ca4-b8bd-b39bbdba2cfe', \
'5b12d099-837e-4769-844c-238212cce983', 'c6bf00ef-ab5e-41bb-8194-7c57d0bbe1d8', 'd4f1f1c0-9368-42f6-a063-99be2cf3c5b4', 'a5c6fc0b-b50d-4da5-bf02-233798f61343', '729e02a0-2fd3-4a10-bd12-569756696c58', \
'd2bb703c-9d66-444e-a968-789ff90fa1e8', 'b1003678-854a-4a6d-9dfc-34fe700efecf', '41cf39ea-6a17-4657-ad64-abd7d3180dd1', 'fd7c9b8b-c45c-4328-8c7b-54a36c917933', '57fcf983-6d26-48b6-92df-a8473dfff5e7', \
'4f4f674c-c809-4143-a0bc-3da1eab97ccb', '0087016e-36b4-40d0-9cf4-192ff293a32b', '18490f67-38dc-4ffb-b63b-25e787f28a7d', '39893579-8a62-473d-8b70-50477684898a', 'bf100acf-b0df-4d5d-8f43-e828fadd0afa', \
'3bb1c621-3383-46bf-98e7-29d8f5a26d35', '04a31ca9-20ed-4ffb-8fdb-8d428bed6e3d', '7cf6f94b-4fd0-4dda-8335-678eeb167532', 'a7c1a305-95e8-42e9-9df0-c7cb30aff512', 'e17aa0bb-7666-4944-abfa-54e09649f767', \
'7c58c1b7-fa59-4f0c-a299-6474c9a819a8', '31ea5b8a-7b28-4066-af64-bfc9e79c5d03', '6ce1db69-9cac-4239-b9a5-a4300940f81e', 'a4efc265-04cb-4ca1-b015-a0de593b705e', 'e47c5ffe-94d7-4620-877a-88f9ae6c74f2', \
'64d6a7cd-88fe-4a92-b958-dc7e1b8d07e7', '373ef775-897f-4e1c-9889-c6a5ad73715a', 'ab9d6a59-71bb-46a2-926e-9e3c4d2e3ed8', 'e1f13bf5-960e-4019-a767-83e3de54b6ba', 'bb3ec9f8-0a37-4f30-8817-0e70018d1648', \
'55cf44dd-4eb5-4d13-ad10-66ca10c90d2e', '6379b4b7-19ca-41a1-8ee8-e940ec78caa2', '41cd474a-e8eb-4b78-9405-e40db5c8b9ef', '4bfc7cca-0961-44df-a622-d29ef7bb2251', '5b3f71a5-59be-4815-aa73-60b09d40e58e', \
'77b4f90a-f7eb-42fd-bfb5-81b2858197f6', '664161dc-d8d8-4f10-9d47-214041cbf516', '93674546-c72a-48dd-ab34-6ec07872813f', 'a340ec91-b12a-41a7-bbb1-3b6bb60da44e', 'ad25757c-7d82-44a4-b460-02f193bc6917', \
'6ca24b9a-8d22-4224-8bc1-545eb52c6c65', '39bd978f-dd93-45a4-ba45-a9e7b82c3b15', '5c80a94a-4800-4b21-ae5e-d95ae5ce0deb', 'cdff3325-f6a9-440f-b015-0e185cb708e2', '68a1283f-e993-4b83-93c2-a957858b3c37', \
'4e7735d7-9384-465f-9584-2170777465df', '02f3ab00-a435-427f-bae4-355fa1a985fa', '0369c35f-3adb-4cc3-872f-4411dc0b304a', '55fb92f4-cb99-46ed-84e9-29cb0ed180a7', '71289756-9189-4ba3-bde3-1d92bfe360fa', \
'42200454-9652-4e51-ad1c-24a5588f1ee8', 'a6069e4f-32e1-4c3f-a362-9cf7307d2ca6', '999c8f86-6dc7-4215-a24a-d6b605f0631b', '55db2c75-bb99-4f37-8807-e436e628b67d', '157d4f51-7acf-42ac-bb02-1a2f0cfe4834', \
'9b10d4d2-2c44-4981-8001-14efb336c322', 'e5048ed0-ce01-4db9-a16b-8b99f7ab519a', '3699bcc2-3c1d-4af6-9233-325c5e5d991e', 'c154d293-ff86-421f-b1d9-6c8074ab836d', 'be96f725-6451-4b18-96f6-7a13dbf79411', \
'285c338f-4f2b-462c-a661-12370166edcd', '9c8f4547-fe4f-4fd1-9340-63bb4539d3aa', '9cc656c5-0ce7-40ac-8709-2411760abd06', 'fa20488e-8464-49c9-a7e8-b9e9a2864e81', 'b1e8ede9-516e-4cca-8244-0f085983321d', \
'c1dc2e08-0771-49bb-a437-6d2479a76a77', '01934493-72bf-4d15-9cfe-c4bc4ddbe4ca', '9d21a764-779d-4ba8-b6e9-eacb5bac0431', '3c338228-13a5-4132-af5a-1958894ff685', 'bc8d55b6-d7c5-49fa-b73b-cec8709bf1de', \
'6e4b0af9-e7ec-446b-96d1-44d6cf1e8de8', '8d783cbb-fe24-4050-8e97-b2b87ada0377', '41b093f2-42ae-4bc4-a960-182e659209a5', 'd5e3ea4e-9b8a-4862-a674-9c26dc9d077e', '28bcc495-94dd-4b5b-a573-99234fd801af', \
'e03983fe-b521-4aae-849e-0b17596ea69b', '454c3763-d534-4e99-be8f-9f8321b8ae34', '31efa7fa-db39-4299-b1b9-2f0a85e8edb0', 'e3bcfe8c-375a-4585-a705-c9cb7fb5e2d4', 'cbf52dc9-3a2a-487f-8fbb-aca4f4bd4380', \
'1076144b-2a24-439b-ae73-1cd15b1b8844', '49c67d80-67a6-4382-8483-5489908bd777', '5089b36e-8ccc-4a66-95b2-01f62a9ec2fa', 'd74f17eb-a784-455e-aafd-d07c318e0ae8', '3fdc0db1-2cd5-4164-825a-dc6b6b225eaa', \
'54d06db3-0fd8-4b83-8766-a28e361bc7b4', '99a919c7-0ce6-4cda-9427-573f947f5b4a', '8832a5cd-f587-4bf9-8584-00483fd57a49', 'b939d999-d427-4ce3-b1c1-bea1df89ca16', 'fe05c1ea-c65b-4388-9787-4dfa1dc4dda7', \
'78e99688-f09d-4212-8691-173734f2fa1c', '8c876d51-fc4a-4a37-aee7-1fdbe0334e55', '3b39545e-397e-48c8-b473-df77469888bf', '74e107ef-6e9c-4a49-9440-53a5af8db3bc', '6d59ee60-404f-4356-906d-4216c1623c6c', \
'73a7dbb4-5e47-49b0-9b44-c851265b5bf0', '8b541157-07a5-47f8-bb2e-f785825f07b6', '7d8a88f0-8247-4825-bf1a-6548696d657c', 'e3a6f513-1a82-41b4-94cb-8aca31d58c3a', '72d3fe73-cbe1-4ca0-b609-6662062c4ed1', \
'25986292-f10d-4f02-98d0-fbb3d483b797', '83dafe47-02ac-4ddc-8e21-4333ad8f81c6', '406b208e-b644-422c-8104-c4ba26ec2a7f', '846782f7-ef45-405f-a980-a89ec725d00e', 'e04e5d78-dca9-406e-93c0-9b7085a75de4', \
'6e7af708-4ec0-41ca-be00-26545c130e9f', '4218b529-b76c-4a78-884b-96488bbe7f77', '31be6f4e-669e-4884-a9a3-85c6537dc0b9', 'f680119a-bbf2-4186-a2a6-400107011ed2', 'd6f3eec3-1cd6-4a22-b992-83358c21c9e1', \
'bd39a8b0-c3a0-4f6e-a8e1-5054d2d91c74', '698a3f0d-cf38-4033-a4db-f748bc5be55f', '2d26d958-d336-4630-b607-c4b59f9c55d2', '503764f3-d050-44cf-8ea4-d5f73bae4bed', 'b6e3d3cf-ede7-4b41-bdf0-21bb3b0a3f0b', \
'faf2d0bd-0297-401d-affe-a6f9edffe40e', '5cbfc21d-d8cf-417a-aa1a-bc3d9ede9ea8', '9b398bf9-1b45-4e03-b305-9e9da177027b', 'f8041b44-cdb7-4ae9-9ab9-79e672ca9e23', '57a05f31-2409-47e3-882e-17c4d7af1ea7', \
'2a3a2f99-6dba-44b8-8e4f-c9ce112be9f0', 'a8964b16-471a-4934-b826-f1686250c332', 'fd873e50-ab00-4cf3-a60e-8a8bdddf01a1', '6459af83-60c1-4642-bdab-d95ba39aa7d1', '3c058029-cda0-42de-893f-3f525bb75295', \
'9302277c-706b-4af9-9993-fd41126704e0', '49b73925-72a4-4ea5-8de3-edbd3d0e5fd3', 'bdc5a9c3-2721-46ba-9164-670830e15a3c', 'af7a5c0a-4b00-4ece-8d8c-fa3c4afcb397', '8f296d0e-6b89-45f2-8df0-2c895e1af404', \
'd5b04687-c13d-4561-93f6-11b41e46cdaa', 'fdaefbe9-cc64-4e6f-98ac-518ac3c56ff5', '2f082edb-1bc5-41bf-abda-850694b9844e', 'cb5fcd88-e6aa-4319-a0b7-4e916cdff435', 'f793a5a9-57a5-4318-b715-28a4c5e08251', \
'4a6c154e-3283-4cef-9006-3e0c2e0b6dcc', '861b5a73-9fab-470d-b244-b856a6917a8d', 'b61fe6b0-326f-4831-bafd-8e58ce52100a', 'c9233c19-97b0-4d7c-8d29-4a3bbe0dcbaf', '13949999-a0a4-48c7-abcc-95434bad05e0', \
'7bdbfaa6-e063-4b62-89ca-f8eb1149f8db', '400de097-7514-47ef-8492-df7dd1635a68', '7d5cde34-ae9b-461a-9c4f-f246bba14de1', 'e44c460d-16d3-47df-9648-50a3be5e9f56', 'fc8f4bfc-ee63-42f4-aec1-9c01dee9865c', \
'2cbec75c-44f3-42b1-a236-b162ffda3b9e', '7594b534-f451-4bd4-a492-7be61139dcce', 'd8407407-437a-4dfa-9535-dbcf8fee5be6', 'ac858dd8-d0bb-4406-a38c-3beffdd64890', 'b9ecf89b-75de-4a1d-832f-7c167b862a81', \
'b24d76e2-f71c-4ffd-b3fb-58fc3faeaab2', '6f269a8a-a0df-4b8d-a620-793ddc3d0d11', 'bda25e60-9d88-4b1c-97c9-928a3d4b1fb9', '044943ee-644b-4a0a-8c46-c23fcf6dcf10', '3647e2aa-0382-439f-aec7-0fcb4089ef85', \
'3d50f527-ca92-49e7-9359-247de0609150', 'e2532f8a-c801-4869-a9e9-94fcecb81fbd', '8e1ff3e1-f0da-4d71-b663-7380fc6b9a70', '7462f1fd-f496-4a00-94e7-1d6d361f10d9', 'b481fb5f-1890-4551-ba78-1c2c022152c2', \
'c4c75b61-72db-4c62-abba-b8b557b52fd4', 'e9129880-94ff-4603-a0aa-5a29d097807c', 'c7423118-f4ea-47db-a93b-483c0479028a', '764747e7-bc24-4cdd-bbe6-148d6817c55f', '4d795c01-db87-4523-972a-16ca9e81c990', \
'8577fdf1-37ef-4680-b2ed-c0f59fe9c6e9', '23946fc4-6960-4ce3-968c-6e1ea32c7903', '158ca0a9-3eb6-47da-aa60-ff3db2bf5525', 'ea147776-7909-403b-aa2e-9a941862f2f6', '62e32dc7-c86d-41cd-afcd-5c174ef8a7b0', \
'586e87bf-6898-4d48-bf82-9cafb7e4cab0', '6df60e99-4005-44b1-abd1-ff1895a04b3e', 'fa42aa4e-7d4b-4c8c-aec4-2426c517e55d', '490cca99-8913-41f0-ab82-30a888c91561', 'cc3262b2-4de0-4d39-b3c7-ca268d4ee302', \
'a0c1b20e-981e-48af-baf6-b00a64a4038d', 'f99fd757-71fd-434b-9a18-ac62781889a9', '7cb4e1eb-3f46-40ee-a176-32f852813d98', 'f5fd78e3-22c6-4f87-83b2-d597304714b9', '9e8c4575-8eb8-41cb-bec7-add1c7622da0', \
'fe96ff23-fec1-4442-b4b0-848de9df7cad', 'ddf50368-39ae-460d-89f3-0da5ab464f04', '3a66e741-e17b-43fa-87ea-91f242cb0646', '0ca26fe8-ee95-4c14-b033-993298fdddaa', '20d75f71-8e48-4adb-a4bb-0bd074caf872', \
'1af242a5-527d-46a3-ae4f-0a1142ee1e80', 'b80d1e7d-34ba-4216-b134-8f64e5d42d04', 'de774fb1-ce2f-4767-b1ef-303d7f9f44a5', '21713ef0-c7d3-4047-8a40-b5f8171b6f29', 'f13e759d-1050-4d23-9ba1-6033982ef6de', \
'b006e258-7ee7-4472-a8b4-865c9dd2953d', 'c5c5f71d-abb8-45f1-a312-abf0c4b8ff1b', '15083231-af0d-4680-aaa3-1cd2e83765f8', '378a47d9-88f3-4298-bff3-b38321a2a0cf', '5116192a-974f-442d-ab17-297a428bff7a', \
'f059154e-71f5-482e-a674-3294e0d3a08b', 'ebd5b9ec-f585-476e-8af1-75def3c98644', '544bfb1a-f373-4e80-b79a-07f71dd6f8c1', '592334b2-9d9a-4ecc-a31d-8d99921c7335', '46df7908-ca46-4a29-bf68-9645e8d9f6a4', \
'bc2d6303-edce-4aa4-885d-7c96c2315099', 'add12899-65e7-428c-ae76-23eb71b98270', '34de0af8-6587-4e3b-9166-5251579b4cdf', '52d23894-ea97-4f83-a8d2-c0d50ac8400f', '47feda30-3ab9-4ce9-96e7-8d810a252a2e', \
'0292766a-c7ee-4d01-b3b3-17c148657a02', '9247de53-2a6f-4750-b324-30c4afddc6d9', '0a9fbc34-142a-4f29-aeaf-cfc7bae857de', '4fa4e494-060c-42f5-baf7-5d083d78825a', 'fb93c96f-179f-4050-8ed0-337c28f5364f', \
'77b0284b-f0f9-4e28-a165-b0d414613bcf', '48b27a9d-7117-4567-a576-d7587c81fcf0', '567d4090-c6f7-4f8f-8e0b-dd89a3b3d9d2', 'ce728761-af5c-4ba6-a68d-aa01ad676b8c', 'b6ebacd4-ae80-46ec-aca3-accf2f655696' \
]


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

    def trimQuotes( text ):
        #if surrounded by quotes, removes them
        ld = len( text )
        if ( 1 < ld ):
            if ( ( text[0] == '\'' and text[-1] == '\'' ) or ( text[0] == '\"' and text[-1] == '\"' ) ):
                text = text[1:-1]
        return text
    trimQuotes = staticmethod(trimQuotes)

    def stripComment( text, rightTrim = True ):
        #remove anything after the last '#' unless it is before a dblquote ( ' )
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
            quote   = False
            dblquotes  = False
            escaped = False
            i = 0
            while ( i < lt ):
                c = t[i]
                if ( c == '\n' ):
                    break
                elif ( c == '#' ):
                    if ( not escaped ):
                        if ( not quote and not dblquotes ):
                            pound += 1
                            break
                    escaped = False
                elif ( c == '\'' ):
                    if ( not escaped ):
                        if ( dblquotes ):
                            raise Exception ( 'Unbalanced dblquotes (\") in text: ' + text )
                        quote = not quote
                    escaped = False
                elif ( c == '\"' ):
                    if ( not escaped ):
                        #if ( dblquotes ):
                        #    raise Exception ( 'Unbalanced dblquotes (\") in text: ' + text )
                        dblquotes = not dblquotes
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

    def isExtensionAllowed( filename, allowedExtensionsList ):
        # check if a filename extension is against a list
        # if ( len(filename) > 4 and ( filename[-4:] == '.cpp' or filename[-1:] == '.h' or filename[-4:] == '.inl' ) ):
        allowed = False
        for ext in allowedExtensionsList:
            extlen = len( ext )
            if ( extlen ):
                if ( filename[-extlen:] == ext ):
                    allowed = True
                    break
            else:
                if ( filename.find( '.' ) == -1 ):
                    allowed = True
                    break
        return allowed
    isExtensionAllowed = staticmethod(isExtensionAllowed)

    def findInList( text, list ):
        index = -1
        i = 0
        for txt in list:
            i = i + 1
            if ( txt == text ):
                index = i
                break
        return index
    findInList = staticmethod(findInList)

    def uuidGen():
        #import commands
        uuid = commands.getoutput('uuidgen')
        uuid = uuid.rstrip()
        #for n in range( 1, 100 ):
        #    line = ''
        #    for i in range( 0, 3 ):
        #        #uuid = commands.getoutput('uuidgen')
        #        uuid = StringUtils.uuidGen()
        #        uuid = uuid.rstrip()
        #        line = line + '  ' + uuid
        #    print line
        return uuid
    uuidGen = staticmethod(uuidGen)

    """
    Other  version don't really work
    This works under unix, but at this point it's better to use uuidgen

    def uuid( self ):
        " " "
          Generates a universally unique ID.
          Any arguments only create more randomness.
        " " "
        t = long( time.time() * 1000 )
        r = long( random.random()*100000000000000000L )
        try:
            a = socket.gethostbyname( socket.gethostname() )
        except:
            # if we can't get a network address, just imagine one
            a = random.random()*100000000000000000L
        data = str(t)+' '+str(r)+' '+str(a)+' '+str( '1' )
        data = md5.md5(data).hexdigest()
        return data
    """

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

    # Split a path in head (everything up to the last '/') and tail (the
    # rest).  After the trailing '/' is stripped, the invariant
    # join(head, tail) == p holds.
    # The resulting head will have no slash even if it is the root (major change to npath's implementation ).
    def split(p):
        """Split a pathname.

        Return tuple (head, tail) where tail is everything after the final slash.
        Either part may be empty.

        Used implementation similar to the one of npath so it works in the same way with cygwin/linux !
        The problem is that under cygwin they expect only '/' to be used, so if the path
        contains '\\' then nothing works
        """

        i = max( p.rfind('/'), p.rfind('\\') )
        if ( i != -1 ):
            ( head, tail ) = p[:i+1], p[i+1:]  # now head has the found [back]slash and tail has no slashes
        else:
            ( head, tail ) = '', p

        return ( head, tail )
    split = staticmethod(split)

    # Split a path in root and extension.
    # The extension is everything starting at the last dot in the last
    # pathname component; the root is everything before that.
    # It is always true that root + ext == p.
    def splitext(p):
        """Split the extension from a pathname.

        Extension is everything from the last dot to the end.
        Return (root, ext), either part may be empty.

        Used implementation of npath so it works in the same way with cygwin/linux !
        """

        i = p.rfind('.')
        if ( i <= max( p.rfind('/'), p.rfind('\\') ) ):
            return p, ''
        else:
            return p[:i], p[i:]
    splitext = staticmethod(splitext)

    def basename(p):
         # Return the tail (basename) part of a path.
        """Returns the final component of a pathname"""
        return FileUtils.split(p)[1]
    basename = staticmethod(basename)

    def dirname(p):
    # Return the head (dirname) part of a path.
        """Returns the directory component of a pathname"""
        return FileUtils.split(p)[0]
    dirname = staticmethod(dirname)

    def isUnixOs():
        # needs _names = sys.builtin_module_names
        isUnix = False
        if 'posix' in _names:
            isUnix = True
        elif 'nt' in _names:
            isUnix = False
        elif 'os2' in _names:
            # the workaround is just to test the behaviour of os.path.normpath( '.\test' )
            raise Exception( 'normPath not fully implemented for os2. The workaround is easy if you need' )
        elif 'mac' in _names:
            # the workaround is just to test the behaviour of os.path.normpath( '.\test' )
            raise Exception( 'normPath not fully implemented for mac. The workaround is easy if you need' )
        else:
            # the workaround is just to test the behaviour of os.path.normpath( '.\test' )
            raise Exception( 'normPath not fully implemented for \'unknown os\'. The workaround is easy if you need' )
        return isUnix
    isUnixOs = staticmethod(isUnixOs)

    def normPathSimple( path, unixStyle ):
        # this function is probaly going to slowly replace os.path.normpath()
        if ( unixStyle ):
            path = path.replace("\\", "/")
            path = path.replace("//", "/")      # eliminates doubles
        else:
            path = path.replace("/", "\\")
            path = path.replace("\\\\", "\\")   # eliminates doubles
        return path
    normPathSimple = staticmethod(normPathSimple)

    def normPathOld( path, unixStyle, keepFirstDot=False ):
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
    normPathOld = staticmethod(normPathOld)

    def normPath( path, unixStyle, keepFirstDot = g_KeepFirstDot_False, minPathIsDot = g_MinPathIsDot_True, isDirForSure = g_IsDirForSure_False ):
        # g_IsDirForSure_ChkDot is used because there is an option in vc70 'ObjectFile' such:
        #   'ObjectFile=".\vc70\DebugDLL/"
        # that *WANTS* the '/' at the end if it is not a file otherwise it compiles only in a 'partial' and weird way !!!

        # gets rid of exceding './' ( included the first ) and of the final '/'
        if ( path == '' ):
            return path

        hadCurr = False
        if ( unixStyle ):
            sep = '/'
            curr = './'
        else:
            sep = '\\'
            curr = '.\\'

        # we need to do this first otherwise problems under cygwin when unixStyle=True but the path starts with r'.\'
        path = FileUtils.normPathSimple( path, unixStyle )

        if ( path == '.' or path == curr ):
            if ( path == '.' ):
                if ( isDirForSure == g_IsDirForSure_True or isDirForSure == g_IsDirForSure_ChkDot ):
                    # in this way we make sure we have the '/' at the end
                    path = curr
            else:
                if ( keepFirstDot ):
                    path = curr
                else:
                    if ( not minPathIsDot ):
                        path = ''
            return path

        if ( path and path[0] == '.' ):
            if ( 1 < len(path) and path[1] in '/\\' ):
                hadCurr = True

        isUnix = FileUtils.isUnixOs()

        # nothing: this function is used also with paths like: 'AdditionalIncludeDirectories="$(VCF_INCLUDE),$(VCF_INCLUDE)/../thirdparty/common/agg/include/"
        if ( re_find_one_of_non_path_char.search( path ) ):
            normalize = False
        else:
            normalize = True

        # eliminates the first './' unless it is just that BUT ONLY UNDER nt, not under unix/posix !
        if ( normalize ):
            path = os.path.normpath( path )
        else:
            pass

        # brute force, because I am tired of coding this. I just need it working !
        stillHasCurr = False
        if ( path and path[0] == '.' ):
            if ( 1 < len(path) and path[1] in '/\\' ): # this check is necessary to do it again on unix/cygwin
                stillHasCurr = True

        if ( stillHasCurr ):
            if ( not keepFirstDot ):
                path = path[2:]
            elif ( keepFirstDot == g_keepFirstDot_StandardVc ):
                if ( 3 < len(path) and path[2] == '.' and path[3] == '.' ):
                    path = path[2:]
        else:
            if ( keepFirstDot ):
                if ( not FileUtils.isAbsolutePath( path ) ):
                    add = False
                    # never with '../'
                    if ( keepFirstDot == g_KeepFirstDot_AddOnlyIfNoDots or keepFirstDot == g_keepFirstDot_StandardVc ):
                        if ( 1 < len(path) and not ( path[0] == '.' and path[1] == '.' ) ):
                            add = True
                    else:
                        add = True
                    if ( add and path and not path[0] == '$' ):
                        path = curr + path

        # again unfortunately, because of os.path.normpath(). In the future implement just normPathSimple
        path = FileUtils.normPathSimple( path, unixStyle )

        if ( isDirForSure == g_IsDirForSure_True ):
            if ( path and not path[-1] in '/\\' ):
                # the standard is '/' not '\', always !!!
                path = path + g_dir_final_separator
        elif ( isDirForSure == g_IsDirForSure_ChkDot ):
            if ( not path[-1] in '/\\' ):
                # use FileUtils.splitext() in the future
                i = path.rfind( '/' )
                if ( i == -1 ):
                    i = path.rfind( '\\' )
                # does it have a dot ?
                j = path.rfind( '.' )
                if ( i < j ):
                    # yes. we guess it is a filename
                    pass
                else:
                    # yes. we guess it is a directory and we add the sep
                    # and not when we have something like: "$(VCF_LIB)\"
                    if ( path and not path[-1] == ')' ):
                        # the standard is '/' not '\', always !!!
                        path += g_dir_final_separator
            else:
                #it is a dir for sure and with the '/' at the end
                if ( path ):
                    # the standard is '/' not '\', always !!!
                    path = path[:-1] + g_dir_final_separator
                pass

        # we fix this always if we decide to ( with g_fix_last_slash_in_path )
        if ( g_fix_last_slash_in_path ):
            # no '.\' at the beginning when we have something like: "$(VCF_LIB)"
            if ( 3 < len( path ) and path[2] == '$' and path[1] in '/\\' and path[0] == '.' ):
                path = path[2:]
            # no '/' at the end when we have something like: "$(VCF_LIB)"
            if ( path and path[-2] == ')' and path[-1] in '/\\' ):
                path = path[:-1]

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

    def isRelativePath( pathname ):
        return ( not FileUtils.isAbsolutePath( pathname ) )
    isRelativePath = staticmethod(isRelativePath)

    def isAbsolutePath( pathname ):
        if ( not pathname ):
            raise Exception( 'FileUtils.isAbsolutePath: path empty' )
        (drive,path) = os.path.splitdrive( pathname )
        isAbsolute = ( len( drive ) or ( path and path[0] in '/\\' ) )
        return isAbsolute
    isAbsolutePath = staticmethod(isAbsolutePath)

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

            # eliminates the first './' because './../subdir' vould be seen as a malformed path
            if ( rpath and rpath[0] == '.' ):
                if ( 1 < len(rpath) and rpath[1] == '/' ):
                    rpath = rpath[2:]
                    rp = rpath.find( '../' )

            while ( rp != -1 ):
                rp = rpath.find( '../' )
                if ( rp != 0 ):
                    if ( rp == -1 ):
                        break
                    # we consider a path like foo/../bar is malformed (that's not really true, but it quicly shows mistakes somewhereelse
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

    def relativePath( basepath, path, minPathIsDot, unixStyle, addFirstDot = True ):
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

                if ( not addFirstDot ):
                    if ( path[:2] == './' ):
                        path = path[2:]

            else:
                if ( rpath == '.' ):
                    path = ''
                else:
                    path = rpath
                    if ( wasDirectoryForSure ):
                        path += sep

                if ( not addFirstDot ):
                    if ( path[:2] == './' ):
                        path = path[2:]

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

                if ( not addFirstDot ):
                    if ( path[:2] == './' ):
                        path = path[2:]

                if ( not unixStyle ):
                    path = path.replace("/", "\\")

        return path
    relativePath = staticmethod(relativePath)


################################################################################
# OptionEx is used to subclass the Option class in an effor to add flexibility to the use of the command line options
# Even if still used by the script, the effort substantially failed
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
    dbg = StringUtils.trimQuotes( dbg )
    rls = StringUtils.trimQuotes( rls )
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
    TYPE_CHECKER["extend"]  = tck_getExtendValues
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
# The options list is first created by the call optparser.parse_args
# But because we also use a configuration file and we still want the command line options to have priority
# on the options given by the configuration file, then we need to find out which options
# have been really given by the user on the command line
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

        self.filenameLog = ""
        self.fdFilenameLog = None
        self.filenameLogDup = ""
        self.fdFilenameLogDup = None


        # manages command line options
        self.hasOptions = False

        self.usage = "usage: %prog [-f] [-r] [-q] [-v] other args"
        self.version = "%prog - ver 1.0.0 - 13 mar 2004"

        self.allowedDirsList = []
        self.allowedAbsoluteDirsList = []
        self.excludedSubdirsList = []
        self.allowedExtensionsList = []

        self.conformLibrariesList = {}

        self.librariesChangePostfixListLwr = {}
        self.librariesChangePostfixDictList = {}
        self.librariesChangePostfixDictDict = {}
        self.librariesChangePostfixPrintString = ''

        self.projectsNoPostfixList = []
        self.projectsNoPostfixMainNameLwrList = []
        self.projectsNoPostfixMainNameLwrDict = {}

        self.projectsNoPostfixOutputList = []
        self.projectsNoPostfixOutputMainNameLwrList = []
        self.projectsNoPostfixOutputMainNameLwrDict = {}

        self.projectsNoPostfixIfUnderCompilerDirList = []
        self.projectsNoPostfixIfUnderCompilerDirMainNameLwrList = []
        self.projectsNoPostfixIfUnderCompilerDirMainNameLwrDict = {}

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
        self.allProjectNamesLwrPathsDict = {}

        # this variable is introduced in order to have the table referenceSolution.dictSlnProjectDataByName filled up gradually
        self.getProjectDataForEachProject = False

        self.resetCounts()
        self.resetTotCounts()

        self.numErrors = 0
        self.numWarnings = 0

        # keeps track of the used uuid grom the g_uuidList
        self.lastUuidIndex = -1
        self.allUsedUuidsDict = {}
        self.allUsedProjUuidsDict = {}

        #self.configsection = ''
        optparser = OptionParser( usage=self.usage, version=self.version, option_class=OptionEx )
        optparser.add_option(   "-c", "--config"                             , type = "string"  , dest = "config"                        , default=g_default_config      , help="configuration file" )
        optparser.add_option(   "-s", "--section"                            , type = "string"  , dest = "section"                       , default=g_default_section     , help="section in the configuration file" )

        optparser.add_option(   "--workingDir"                               , type = "string"  , dest = "workingDir"                    , default='.'                   , help="set the current directory, it uses os.getCwd() if empty" )

        optparser.add_option(   "-f", "--file"                               , type = "string"  , dest = "filename"                      , default=""                    , help="process only filenames containing this string ( lettercase is ignored )" )
        optparser.add_option(   "-r", "--recurse"                            , type = "int"     , dest = "recurse"                       , default=False                 , help="recursion into subdirectories" )

        optparser.add_option(   "-v", "--verbose"                            , type = "int"     , dest = "verbose"                       , default=0                     , help="verbose level. Use -vvv to set verbose level = 3" )
        optparser.add_option(   "-e", "--errorLevel"                         , type = "int"     , dest = "errorLevel"                    , default=1                     , help="error level. ( 3 < errorLevel ) --> stop on first error. Use -eee to set warning level = 3" )
        optparser.add_option(   "-w", "--warning"                            , type = "int"     , dest = "warning"                       , default=1                     , help="warning level. Use -www to set warning level = 3" )
        optparser.add_option(   "-l", "--log"                                , type = "int"     , dest = "log"                           , default=0                     , help="logging into a file" )
        # optparser.add_option(   "-q", "--quiet"                              , type = "int"    , dest = "verbose"                       , default=False                 , help="reset verbose level to zero" )

        optparser.add_option(   "-p", "--prompt"                             , type = "int"     , dest = "prompt"                        , default=True                  , help="ask to press any key before continuing" )

        optparser.add_option(   "--enableProjectFilesModif"                  , type = "int"     , dest = "enableProjectFilesModif"       , default=False                 , help="disable any kind of changes in the project files content ( *.dsp and *.vcproj ). To see any problems. But no modifications." )
        optparser.add_option(   "--enableSourceFilesModif"                   , type = "int"     , dest = "enableSourceFilesModif"        , default=False                 , help="disable any kind of changes in the source files content ( *.h and *.cpp ). To see any problems. But no modifications." )

        optparser.add_option(   "-u", "--unixStyle"                          , type = "int"     , dest = "unixStyle"                     , default=False                 , help="when True uses \'/\' instead than \'\\\' ( suggested False: sln files want windows style )" )
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

        optparser.add_option(   "--copyToIcl7"                               , type = "int"     , dest = "copyToIcl7"                    , default=True                  , help="copy dsp files in corresponding directories for icl7 ( option VCF specific )" )
        optparser.add_option(   "--copyToVc70"                               , type = "int"     , dest = "copyToVc70"                    , default=True                  , help="copy dsp files in corresponding directories for vc70 ( option VCF specific )" )
        optparser.add_option(   "--copyToVc71"                               , type = "int"     , dest = "copyToVc71"                    , default=True                  , help="copy dsp files in corresponding directories for vc71 ( option VCF specific )" )
        optparser.add_option(   "--synchVcprojSln"                           , type = "int"     , dest = "synchVcprojSln"                , default=True                  , help="only with (copyToVc7x==1). instead then duplicating dsp files it synchronizes the corresponding vcproj unless it does not exists" )
        optparser.add_option(   "--keepDspCopy"                              , type = "int"     , dest = "keepDspCopy"                   , default=True                  , help="only with (synchVcprojSln==1). instead then duplicating dsp files it synchronizes the corresponding vcproj unless it does not exists" )

        optparser.add_option(   "--allowDirs"                                , type = "int"     , dest = "allowDirs"                     , default=True                  , help="works only with selected directories and its subdirectories" )
        optparser.add_option(   "--excludeSubdirs"                           , type = "int"     , dest = "excludeSubdirs"                , default=False                 , help="exclude the subdirectories containing the strings specified in the excludeSubdirs section" )
        optparser.add_option(   "--allowedExtensions"                        , type = "string"  , dest = "allowedExtensions"             , default=''                    , help="allowedExtensions" )

        optparser.add_option(   "--fixFilenamePostfix"                       , type = "int"     , dest = "fixFilenamePostfix"            , default=False                 , help="checks for the correctness of postfixes ( like \'_vc70_sd\' ) of filename entries and fixes them. Suggested put it back to False when not used ( works only for vcproj files and fixes probable bug of vc7 compiler. See note end of script )" )

        optparser.add_option(   "--dependenciesWorkspace"                    , type = "string"  , dest = "dependenciesWorkspace"         , default=''                    , help="dependency where to copy all the dependencies from" )
        optparser.add_option(   "--referenceSolution"                        , type = "string"  , dest = "referenceSolution"             , default=''                    , help="reference solution: mainly used to keep the original uuids" )


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

    def __del__(self):
        self.logFileClose()
        #print "del dspApp"
        pass

    def resetCounts( self ):
        self.changedFiles   = 0
        self.unchangedFiles = 0
        self.createdFiles   = 0
        return

    def resetTotCounts( self ):
        self.changedFilesTot   = 0
        self.unchangedFilesTot = 0
        self.createdFilesTot   = 0
        return

    def getcwd( self ):
        # this function was introduced as a temporary workaround to a problem with Cygwin:
        #   OSError: [Errno 2] No such file or directory: '\\mntdos\\vcfcode\\devel\\vcf\\'
        # Solution: it is necessary to put g_internal_unixStyle = True under Cygwin
        cwd = os.getcwd()
        if ( self.hasOptions ):
            cwd = FileUtils.normPathSimple( cwd, g_internal_unixStyle )
        else:
            raise Exception( 'app.getcwd: no attrib options yet' )
        return cwd

    def getNextUuid( self, projName ):
        projNameLwr = projName.lower()
        if ( self.allUsedProjUuidsDict.has_key( projNameLwr ) ):
            uuid = self.allUsedProjUuidsDict[ projNameLwr ]
        else:
            uuid = StringUtils.uuidGen()
            #print '[' + uuid + ']'
            isUnix = ( uuid.find( 'is not recognized as an internal or external command' ) == -1 )
            if ( not isUnix ):
                if ( g_disableUuidgen_on_win32 ):
                    # under win32 I am forced to get the uuid from a table because the uuid algorithms on win32 are pretty bad
                    # this ends up in having a limited number of uuid which can cause problems
                    # so it is suggested use this script under win32 only when debugging, even if I can say
                    # that it is working right also under win32 with the uuids table
                    raise Exception( 'uuidgen is disabled under win32, please disable the option only if you know what you are doing' )
                foundOk = False
                while ( not foundOk ):
                    #raise Exception( 'ERROR: the program needs of unix or cygwin or whatever OS with uuidgen function' )
                    self.lastUuidIndex = self.lastUuidIndex + 1
                    uuid = g_uuidList[ self.lastUuidIndex ]
                    if ( not self.allUsedUuidsDict.has_key( uuid ) ):
                        self.addUuid( uuid, projName )
                        foundOk = True
        return uuid

    def addUuid( self, uuid, projName ):
        projNameLwr = projName.lower()
        self.allUsedUuidsDict[ uuid ] = projNameLwr
        self.allUsedProjUuidsDict[ projNameLwr ] = uuid
        return

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
        print ' --errorLevel     = ' + str(self.options.errorLevel)
        print ' --prompt         = ' + str(self.options.prompt )
        print ' --log            = ' + str(self.options.log)
        print ''

        print ' --enableProjectFilesModif        = ' + str(self.options.enableProjectFilesModif         )
        print ' --enableSourceFilesModif         = ' + str(self.options.enableSourceFilesModif          )
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
        print ' --deleteSccLines                 = ' + str(self.options.deleteSccLines                  )
        #print ' --deleteLineString               = \'' + str(self.options.deleteLineString              ) + '\''
        print ' --reformatOutputIntermediateDirs = ' + str(self.options.reformatOutputIntermediateDirs  )
        print ' --reformatOptionOutput           = ' + str(self.options.reformatOptionOutput            )
        print ''
        print ' --fixFilenamePostfix             = ' + str(self.options.fixFilenamePostfix              )
        print ''
        print ' --dependenciesWorkspace          = ' + str(self.options.dependenciesWorkspace           )
        print ' --referenceSolution              = ' + str(self.options.referenceSolution               )

        print ''
        print ' --reformatOptionOptimize         = ' + str(self.options.reformatOptionOptimize          )
        print ' --reformatOptionPdb              = ' + str(self.options.reformatOptionPdb               )
        print ' --reformatOptionBrowse           = ' + str(self.options.reformatOptionBrowse            )

        print ' --copyToIcl7                     = ' + str(self.options.copyToIcl7                      )
        print ' --copyToVc70                     = ' + str(self.options.copyToVc70                      )
        print ' --copyToVc71                     = ' + str(self.options.copyToVc71                      )
        print ' --synchVcprojSln                 = ' + str(self.options.synchVcprojSln                  )
        print ' --keepDspCopy                    = ' + str(self.options.keepDspCopy                     )

        print ' --allowedExtensions              = \'' + str(self.options.allowedExtensions             ) + '\''

        print ' --allowDirs      = ' + str(self.options.allowDirs)
        if ( self.options.allowDirs ):
            print '   ' + str( self.allowedDirsList )

        print ' --excludeSubdirs = ' + str( self.options.excludeSubdirs )
        if ( self.options.excludeSubdirs ):
            print '   ' + str( self.excludedSubdirsList )

        print '   ' + 'librariesChangePostfix:'
        if ( self.librariesChangePostfixPrintString ):
            # print '   ' + '  ' + str( self.librariesChangePostfixDictList ) # this does not respect the order
            print '   ' + '  ' + self.librariesChangePostfixPrintString

        print '   ' + 'projectsNoPostfixList:'
        print '   ' + '  ' + str( self.projectsNoPostfixList )

        print '   ' + 'projectsNoPostfixOutputList:'
        print '   ' + '  ' + str( self.projectsNoPostfixOutputList )

        print '   ' + 'projectsNoPostfixIfUnderCompilerDirList:'
        print '   ' + '  ' + str( self.projectsNoPostfixIfUnderCompilerDirList )

        print ''

        # giving time to see the output
        time.sleep( 2 )

        return

    def configGetStr( self, section, option ):
        s = self.config.get( section, option )
        s = StringUtils.stripComment( s )
        s = StringUtils.trimQuotes( s )
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
        # read all options from the reformatVc.ini configuration file

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
                    section_librariesChangePostfix              = self.configGetStr ( comm_sect, 'section_librariesChangePostfix' )
                    section_projectsNoPostfix                   = self.configGetStr ( comm_sect, 'section_projectsNoPostfix'      )
                    section_projectsNoPostfixOutput             = self.configGetStr ( comm_sect, 'section_projectsNoPostfixOutput')
                    section_projectsNoPostfixIfUnderCompilerDir = self.configGetStr ( comm_sect, 'section_projectsNoPostfixIfUnderCompilerDir' )

                    self.options.filename                       = self.getOptionValue( [ 'filename', 'f' ]                   , comm_sect, 'filename'                       , "string"    )

                    self.options.recurse                        = self.getOptionValue( [ 'recurse', 'r' ]                    , comm_sect, 'recurse'                        , "bool"      )
                    self.options.verbose                        = self.getOptionValue( [ 'verbose', 'v' ]                    , comm_sect, 'verbose'                        , "int"       )
                    self.options.warning                        = self.getOptionValue( [ 'warning', 'w' ]                    , comm_sect, 'warning'                        , "int"       ) # was comm_sect, 'verbose' ! fixed April 2004
                    self.options.errorLevel                     = self.getOptionValue( [ 'errorLevel', 'e' ]                 , comm_sect, 'errorLevel'                     , "int"       )
                    self.options.prompt                         = self.getOptionValue( [ 'prompt', 'p' ]                     , comm_sect, 'prompt'                         , "int"       )
                    self.options.log                            = self.getOptionValue( [ 'log', 'l' ]                        , comm_sect, 'log'                            , "int"       )

                    self.options.enableProjectFilesModif        = self.getOptionValue( [ 'enableProjectFilesModif'  ]        , spec_sect, 'enableProjectFilesModif'        , "bool"      )
                    self.options.enableSourceFilesModif         = self.getOptionValue( [ 'enableSourceFilesModif'   ]        , spec_sect, 'enableSourceFilesModif'         , "bool"      )

                    self.options.unixStyle                      = self.getOptionValue( [ 'unixStyle' ]                       , comm_sect, 'unixStyle'                      , "bool"      )
                    self.options.deleteSccLines                 = self.getOptionValue( [ 'deleteSccLines' ]                  , comm_sect, 'deleteSccLines'                 , "bool"      )
                    #self.options.deleteLineString               = self.getOptionValue( [ 'deleteLineString' ]                , comm_sect, 'deleteLineString'               , "string"    )

                    self.options.reformatOutputIntermediateDirs = self.getOptionValue( [ 'reformatOutputIntermediateDirs' ]  , comm_sect, 'reformatOutputIntermediateDirs' , "int"       )
                    self.options.reformatOptionOutput           = self.getOptionValue( [ 'reformatOptionOutput' ]            , comm_sect, 'reformatOptionOutput'           , "dbgrlsN"   )

                    self.options.fixFilenamePostfix             = self.getOptionValue( [ 'fixFilenamePostfix'  ]             , comm_sect, 'fixFilenamePostfix'             , "bool"      )

                    self.options.dependenciesWorkspace          = self.getOptionValue( [ 'dependenciesWorkspace' ]           , comm_sect, 'dependenciesWorkspace'          , "string"    )
                    self.options.referenceSolution              = self.getOptionValue( [ 'referenceSolution' ]               , comm_sect, 'referenceSolution'              , "string"    )

                    self.options.enableVcfSpecific              = self.getOptionValue( [ 'enableVcfSpecific' ]               , comm_sect, 'enableVcfSpecific'              , "bool"      )
                    self.options.modifyVc6                      = self.getOptionValue( [ 'modifyVc6' ]                       , comm_sect, 'modifyVc6'                      , "bool"      )

                    self.options.workingDir                     = self.getOptionValue( [ 'workingDir' ]                      , comm_sect, 'workingDir'                     , "string"    )
                    self.options.allowDirs                      = self.getOptionValue( [ 'allowDirs' ]                       , comm_sect, 'allowDirs'                      , "bool"      )
                    self.options.excludeSubdirs                 = self.getOptionValue( [ 'excludeSubdirs' ]                  , comm_sect, 'excludeSubdirs'                 , "bool"      )
                    self.options.allowedExtensions              = self.getOptionValue( [ 'allowedExtensions'        ]        , comm_sect, 'allowedExtensions'              , "string"    )


                    # specific section
                    self.options.createWorkspaces               = self.getOptionValue( [ 'createWorkspaces' ]                , spec_sect, 'createWorkspaces'               , "bool"      )
                    self.options.duplicateWorkspaces            = self.getOptionValue( [ 'duplicateWorkspaces' ]             , spec_sect, 'duplicateWorkspaces'            , "bool"      )
                    self.options.conformLibraries               = self.getOptionValue( [ 'conformLibraries' ]                , spec_sect, 'conformLibraries'               , "bool"      )

                    self.options.reformatOptionOptimize         = self.getOptionValue( [ 'reformatOptionOptimize' ]          , spec_sect, 'reformatOptionOptimize'         , "dbgrlsS"   )
                    self.options.reformatOptionPdb              = self.getOptionValue( [ 'reformatOptionPdb' ]               , spec_sect, 'reformatOptionPdb'              , "dbgrlsN"   )
                    self.options.reformatOptionBrowse           = self.getOptionValue( [ 'reformatOptionBrowse' ]            , spec_sect, 'reformatOptionBrowse'           , "dbgrlsN"   )
                    self.options.copyToIcl7                     = self.getOptionValue( [ 'copyToIcl7' ]                      , spec_sect, 'copyToIcl7'                     , "bool"      )
                    self.options.copyToVc70                     = self.getOptionValue( [ 'copyToVc70' ]                      , spec_sect, 'copyToVc70'                     , "bool"      )
                    self.options.copyToVc71                     = self.getOptionValue( [ 'copyToVc71' ]                      , spec_sect, 'copyToVc71'                     , "bool"      )
                    self.options.synchVcprojSln                 = self.getOptionValue( [ 'synchVcprojSln' ]                  , spec_sect, 'synchVcprojSln'                 , "bool"      )
                    self.options.keepDspCopy                    = self.getOptionValue( [ 'keepDspCopy' ]                     , spec_sect, 'keepDspCopy'                    , "bool"      )

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
                self.currentdir = FileUtils.absolutePath( self.getcwd(), self.currentdir, g_internal_unixStyle )

        if ( self.options.allowDirs ):
            if ( self.config.has_section( section_dirlist ) ):
                pairs = self.config.items( section_dirlist )
                self.allowedDirsList = []
                for pair in pairs:
                    ( name, namedir ) = pair
                    namedir = StringUtils.stripComment( namedir )
                    namedir = StringUtils.trimQuotes( namedir )
                    namedir = namedir.lower()
                    namedir = FileUtils.normDir( namedir, g_internal_unixStyle, True )
                    self.allowedDirsList.append( namedir )
                    absNamedir = FileUtils.absolutePath( self.currentdir, namedir, g_internal_unixStyle )
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
                    namedir = StringUtils.trimQuotes( namedir )
                    namedir = namedir.lower()
                    namedir = FileUtils.normDir( namedir, g_internal_unixStyle )
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
                    if ( item.find( '-->' ) != -1 or item.find( '<--' ) != -1 ):
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


        if ( section_librariesChangePostfix ):
            if ( self.config.has_section( section_librariesChangePostfix ) ):
                self.makeChangeLibrariesPostfixList( section_librariesChangePostfix )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_librariesChangePostfix, self.options.config ) )

        if ( section_projectsNoPostfix ):
            if ( self.config.has_section( section_projectsNoPostfix ) ):
                self.makeProjectsNoPostfixList( section_projectsNoPostfix )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_projectsNoPostfix, self.options.config ) )

        if ( section_projectsNoPostfixOutput ):
            if ( self.config.has_section( section_projectsNoPostfixOutput ) ):
                self.makeProjectsNoPostfixOutputList( section_projectsNoPostfixOutput )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_projectsNoPostfixOutput, self.options.config ) )

        if ( section_projectsNoPostfixIfUnderCompilerDir ):
            if ( self.config.has_section( section_projectsNoPostfixIfUnderCompilerDir ) ):
                self.makeProjectsNoPostfixIfUnderCompilerDirList( section_projectsNoPostfixIfUnderCompilerDir )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_projectsNoPostfixIfUnderCompilerDir, self.options.config ) )

        if ( self.options.createWorkspaces ):
            if ( self.config.has_section( section_createWorkspaces ) ):
                pairs = self.config.items( section_createWorkspaces )
                self.createWorkspacesList = []
                for pair in pairs:
                    ( name, workspace ) = pair
                    workspace = StringUtils.stripComment( workspace )
                    workspace = StringUtils.trimQuotes( workspace )
                    # please, make sure the name contains the dirname too
                    workspace = FileUtils.relativePath( self.currentdir, workspace, True, g_internal_unixStyle )
                    if ( workspace == '.' + FileUtils.getNormSep( g_internal_unixStyle ) ): workspace = ''
                    # workspace = workspace.lower()
                    # workspace = FileUtils.normDir( workspace, g_internal_unixStyle )
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
                    workspace = StringUtils.trimQuotes( workspace )
                    # please, make sure the name contains the dirname too
                    workspace = FileUtils.relativePath( self.currentdir, workspace, True, g_internal_unixStyle )
                    if ( workspace == '.' + FileUtils.getNormSep( g_internal_unixStyle ) ): workspace = ''
                    #workspace = workspace.lower()
                    #workspace = FileUtils.normDir( workspace, g_internal_unixStyle )
                    self.duplicateWorkspacesList.append( workspace )
            else:
                raise Exception( 'The section \'%s\' in the config file \'%s\' does not exists !' % ( section_duplicateWorkspaces, self.options.config ) )

        if ( self.options.allowedExtensions ):
            self.allowedExtensionsList = self.options.allowedExtensions.split( ';' )
            pass
        else:
            raise Exception( 'The \'allowed extensions\' list is empty. The format would be like: \".cpp;.h\" in the section \'%s\' in the config file \'%s\'' % ( spec_sect, self.options.config ) )

        return

    def makeLibraryDependencyList( self, section ):
        # function still running but obsolete by fact ( as replaced by the use of app.options.dependenciesWorkspace only )
        # creates a depencencies list from [vcf_staticLibraries] and [vcf_dynamicLibraries] sections
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

    def makeChangeLibrariesPostfixList( self, section ):
        # splits entries like [ c# = proj: lib1, lib2, libn ]
        pairs = self.config.items( section )
        self.librariesChangePostfixListLwr = []
        self.librariesChangePostfixPrintString = '{'
        npairs = 0
        for pair in pairs:
            npairs = npairs + 1
            ( name, item ) = pair
            # c0 = proj: lib1, lib2, libn
            i = item.find( ':' )
            if ( i != -1 ):
                proj = item[:i]
                proj = StringUtils.stripComment( proj )
                proj = proj.strip()

                list = item[i+1:]
                list = StringUtils.stripComment( list )
                list = list.strip()

                projLwr = proj.lower()
                self.librariesChangePostfixListLwr.append( projLwr )

                # creates the list in the stack
                libList = []
                lmLwrList = []
                libDict = {}

                ls = list.split( ',' )
                if ( ls ):
                    self.librariesChangePostfixPrintString += "\'%s\': [" % ( proj )

                for lib in ls:
                    lib = lib.strip()

                    ( ( lp, lf ), ( lb, le ), ( li, lm, lmLwr, cpl ), ( ls, ld ) ) = DspFile.splitPostfixComponents( lib, '' )
                    if ( not lm ):
                        continue

                    libList.append( lib )
                    lmLwr = lm.lower()
                    lmLwrList.append( lmLwr )
                    libDict[ lmLwr ] = ( ( lm, le, lib ), ( ls, ld ) )
                    self.librariesChangePostfixPrintString += "\'%s\', " % ( lib )

                if ( ls ):
                    self.librariesChangePostfixPrintString = self.librariesChangePostfixPrintString[:-2] # eliminates last ', '
                self.librariesChangePostfixPrintString += '], '

                self.librariesChangePostfixDictList[ projLwr ] = libList
                self.librariesChangePostfixDictDict[ projLwr ] = libDict

            else:
                raise Exception( 'Wrong format of the item \'%s = %s\' in the section \'%s\' of the config file \'%s\'\n' \
                                 'The format should be [ c# = proj: lib1, lib2, libn ]' % ( name, item, section, self.options.config ) )


        if ( npairs ):
            self.librariesChangePostfixPrintString = self.librariesChangePostfixPrintString[:-2] # eliminates last ', '
        self.librariesChangePostfixPrintString += '}'

        return

    def makeProjectsNoPostfixList( self, section ):
        # splits entries like [ c# = proj: lib1, lib2, libn ]
        pairs = self.config.items( section )

        # shorter names
        libList = self.projectsNoPostfixList
        lmLwrList = self.projectsNoPostfixMainNameLwrList
        libDict = self.projectsNoPostfixMainNameLwrDict

        # resettting the lists
        libList = []
        lmLwrList = []
        libDict = {}

        for pair in pairs:
            ( name, item ) = pair

            # project1, "project12", project1n
            list = item
            list = StringUtils.stripComment( list )
            list = StringUtils.trimQuotes( list )
            list = list.strip()

            ls = list.split( ',' )
            for lib in ls:
                lib = lib.strip()

                ( ( lp, lf ), ( lb, le ), ( li, lm, lmLwr, cpl ), ( ls, ld ) ) = DspFile.splitPostfixComponents( lib, '' )
                if ( not lm ):
                    continue

                libList.append( lib )
                lmLwr = lm.lower()
                lmLwrList.append( lmLwr )
                libDict[ lmLwr ] = ( lm, le, lib )

            self.projectsNoPostfixList = libList
            self.projectsNoPostfixMainNameLwrList = lmLwrList
            self.projectsNoPostfixMainNameLwrDict = libDict

        return

    def makeProjectsNoPostfixOutputList( self, section ):
        # splits entries like [ c# = proj: lib1, lib2, libn ]
        pairs = self.config.items( section )

        # shorter names
        libList = self.projectsNoPostfixOutputList
        lmLwrList = self.projectsNoPostfixOutputMainNameLwrList
        libDict = self.projectsNoPostfixOutputMainNameLwrDict

        # resettting the lists
        libList = []
        lmLwrList = []
        libDict = {}

        for pair in pairs:
            ( name, item ) = pair

            # project1, "project12", project1n
            list = item
            list = StringUtils.stripComment( list )
            list = StringUtils.trimQuotes( list )
            list = list.strip()

            ls = list.split( ',' )
            for lib in ls:
                lib = lib.strip()

                ( ( lp, lf ), ( lb, le ), ( li, lm, lmLwr, cpl ), ( ls, ld ) ) = DspFile.splitPostfixComponents( lib, '' )
                if ( not lm ):
                    continue

                libList.append( lib )
                lmLwr = lm.lower()
                lmLwrList.append( lmLwr )
                libDict[ lmLwr ] = ( lm, le, lib )

            self.projectsNoPostfixOutputList = libList
            self.projectsNoPostfixOutputMainNameLwrList = lmLwrList
            self.projectsNoPostfixOutputMainNameLwrDict = libDict

        return

    def makeProjectsNoPostfixIfUnderCompilerDirList( self, section ):
        # splits entries like [ c# = proj: lib1, lib2, libn ]
        pairs = self.config.items( section )

        # shorter names
        libList = self.projectsNoPostfixIfUnderCompilerDirList
        lmLwrList = self.projectsNoPostfixIfUnderCompilerDirMainNameLwrList
        libDict = self.projectsNoPostfixIfUnderCompilerDirMainNameLwrDict

        # resettting the lists
        libList = []
        lmLwrList = []
        libDict = {}

        for pair in pairs:
            ( name, item ) = pair

            # project1, "project12", project1n
            list = item
            list = StringUtils.stripComment( list )
            list = StringUtils.trimQuotes( list )
            list = list.strip()

            ls = list.split( ',' )
            for lib in ls:
                lib = lib.strip()

                ( ( lp, lf ), ( lb, le ), ( li, lm, lmLwr, cpl ), ( ls, ld ) ) = DspFile.splitPostfixComponents( lib, '' )
                if ( not lm ):
                    continue

                libList.append( lib )
                lmLwr = lm.lower()
                lmLwrList.append( lmLwr )
                libDict[ lmLwr ] = ( lm, le, lib )

            self.projectsNoPostfixIfUnderCompilerDirList = libList
            self.projectsNoPostfixIfUnderCompilerDirMainNameLwrList = lmLwrList
            self.projectsNoPostfixIfUnderCompilerDirMainNameLwrDict = libDict

        return


    def addProject( self, prjName, prjNameLwr, baseDir, relPath ):
        if ( not self.allProjectNamesLwrDict.has_key( prjNameLwr ) ):
            self.allProjectNamesList.append( prjName )
            self.allProjectNamesLwrDict[ prjNameLwr ] = prjName
            absPrjPath = FileUtils.absolutePath( baseDir, relPath, g_internal_unixStyle )
            self.allProjectPathsList.append( absPrjPath )
            self.allProjectNamesLwrPathsDict[ prjNameLwr ] = absPrjPath

    def checkAllowedDir( self, filename ):
        allow = True
        if ( app.options.allowDirs or app.options.excludeSubdirs ):
            fn = filename.lower()
            #print os.path.split( fn )
            fn = os.path.dirname( fn )
            if ( fn == '' ):
                fn = './'
            fn = FileUtils.normDir( fn, g_internal_unixStyle ) # add last sep

            if ( app.options.allowDirs ):
                allow = False
                fnAbs = FileUtils.absolutePath( app.currentdir, fn, g_internal_unixStyle )
                for subdir in app.allowedAbsoluteDirsList:
                    if ( fnAbs.find(subdir) != -1 ):
                        allow = True
                        break

            if ( allow and app.options.excludeSubdirs ):
                fnRel = FileUtils.relativePath( app.currentdir, fn, True, g_internal_unixStyle )
                for subdir in app.excludedSubdirsList:
                    if ( fnRel.find(subdir) != -1 ):
                        allow = False
                        break

        return allow


    def logFileOpen( self, duplicate = False ):
        if ( not self.options.log ):
            return

        self.filenameLog = g_filenameLog
        self.fdFilenameLog = file( self.filenameLog, 'a' ) # append
        self.fdFilenameLog.write( '\n\n**********************************************\n\n' )

        if ( duplicate ):
            ( root, ext ) = os.path.splitext( g_filenameLog )
            self.filenameLogDup = root + '.2' + ext
            self.fdFilenameLogDup = file( self.filenameLogDup, 'a' ) # append
            self.fdFilenameLogDup.write( '\n\n**********************************************\n\n' )

        return

    def logFileClose( self ):
        if ( not self.options.log ):
            return

        if ( self.fdFilenameLog and not self.fdFilenameLog.closed ):
            self.fdFilenameLog.close()
            print 'log files \'%s\' closed' % self.filenameLog
        if ( self.fdFilenameLogDup and not self.fdFilenameLogDup.closed ):
            self.fdFilenameLogDup.close()
            print 'log files \'%s\' closed' % self.filenameLogDup
        return

    def logFilePrintLine( self, line, console = True, duplicate = False, throw = False ):
        if ( console ):
            print line

        if ( self.options.log ):
            self.fdFilenameLog.write( line + '\n' )

            if ( duplicate or throw ):
                self.fdFilenameLogDup.write( line + '\n' )

        if ( throw ):
            raise Exception( line )

        return

    def isFileIn( self, filename, namelist ):
        found = False
        for name in namelist:
            name = name.lower() # lowercase to make easier to define g_debugFileList
            if ( filename.lower().find( name ) != -1 ):
                found = True
                break
        return found

    def isFileIn2( self, filename ):
        return self.isFileIn(  filename, g_debugFileList )


################################################################################
class GenericFile:
    """Process and reformat any generic kind of files"""
    def __init__( self, filename ):
        self.filename  = ''
        self.filetitle = ''
        self.setFilename( filename )

        self.resetGenericFile()
        return

    def __del__(self):
        #print "del GenericFile"
        pass

    def resetGenericFile( self ):
        self.lines = []
        self.n = 0
        return

################################################################################
class GenericProjectFile( GenericFile ):
    """Process and reformat any generic kind of project files"""

    def __init__( self, filename ):
        GenericFile.__init__( self, filename )

        self.compiler          = ''
        self.compilerUnderscor = ''
        self.compilerSep       = ''
        self.setCompilerStrings( compilerVc6 )

        self.resetGenericProjectFile()
        return

    def __del__(self):
        #print "del resetGenericProjectFile"
        pass

    def resetGenericProjectFile( self ):
        self.storedOptions = []
        self.lastRegexGroupFound = '' # for debug only

        self.isDebugCfg  = []
        self.c = ''
        self.isStaticCfg = []

        self.PropOutputDirList  = []    # directory for output
        self.PropIntermeDirList = []    # directory for intermediate output
        self.OutputDirOutList   = []    # directory for main output ( it is usually the same as PropOutputDirList, but sometimes we want to /out: somewhereelse )
        self.OutputDirOutCustomBuildList = []    # directory for main output ( it is usually the same as PropOutputDirList, but sometimes we want to /out: somewhereelse )

        self.hasCustomBuildList = []
        self.hasCustomBuild = False
        self.hasCustomBuildOutputDirList = []
        self.hasCustomBuildOutputDir = False

        self.configFullNameList = []
        self.configNameList = []
        self.mainFileTitleBase = ''
        self.mainFileTitleBaseCustomBuild = ''
        self.outputExt = ''
        self.outputExtCustomBuild = ''

        self.PropOutputDir  = ''
        self.PropIntermeDir = ''
        self.OutputDirOut   = ''

        self.appType = enumAppTypeNone

        self.trueProjectName = ''
        self.projectName = ''
        self.projectType = ''
        self.configFullName = ''
        self.configName = ''
        self.addKind = enum_ADD_NONE
        self.isAddins = False

        self.resetWarnings()

        return

    def resetWarnings( self ):
        self.warning_done_dirs_different_between_cfgs = False
        self.warning_done_dir_out_different_than_dir_prop = False
        self.warning_done_extension_different_than_expected = False
        self.warning_unknown_configuration_type = False
        return

    def setFilename( self, filename ):
        self.filename = filename
        self.filetitle = os.path.basename( filename )
        return

    def isFileIn( self, filelist ):
        return app.isFileIn( self.filename, filelist )

    def isFileIn2( self ):
        return app.isFileIn( self.filename, g_debugFileList )

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
        ( self.compiler, self.compilerUnderscor, self.compilerSep ) = DspFile.makeCompilerStrings( compiler, g_internal_unixStyle )
        return

    def getCompilerStrings( self ):
        compilerStrings = ( self.compiler, self.compilerUnderscor, self.compilerSep )
        return compilerStrings

    def getDuplicateVcFilename( self, newCompiler, keepFirstDot ):
        return DspFile.makeDuplicateVcFilename( self.filename, self.compiler, newCompiler, g_internal_unixStyle, keepFirstDot )

    def getCompilerFromName( filename, unixStyle, suggestedCompiler = compilerVc6, recurse = True ):
        compiler = suggestedCompiler
        fn = filename.lower()
        filename = FileUtils.normPathSimple( filename, unixStyle )

        trySomethingElse = False
        i = fn.find( compiler )
        if ( i != -1 ):
            ( ocpl, ocplUnderscor, ocplSep ) = DspFile.makeCompilerStrings( compiler, unixStyle )
            ocs = ocplSep.lower()
            if ( ocpl == compilerVc6 ):
                # the directory is vc60 instead then vc6
                sep = FileUtils.getNormSep( unixStyle )
                ocs = ocpl.lower() + '0' + sep
            i = fn.find( ocs )
            if ( i != -1 ):
                return compiler
            else:
                ( bn, ext ) = os.path.splitext( fn )
                ou = ocplUnderscor.lower()
                i = bn.find( ou )
                if ( i != -1 ):
                    return compiler
                else:
                    trySomethingElse = True
        else:
            trySomethingElse = True

        if ( trySomethingElse and recurse ):
            compiler = DspFile.getCompilerFromName( filename, unixStyle, compilerVc70, False )
            if ( compiler ):
                return compiler

            compiler = DspFile.getCompilerFromName( filename, unixStyle, compilerVc71, False )
            if ( compiler ):
                return compiler

            compiler = DspFile.getCompilerFromName( filename, unixStyle, compilerIcl7, False )
            if ( compiler ):
                return compiler

            #if nothing, the only possible compiler is compilerVc6, and we can't know if the name is 'examples/Actions/Actions.dsp'
            return compilerVc6

        return ''
    getCompilerFromName = staticmethod(getCompilerFromName)

    def makeDuplicateVcFilename( filename, oldCompiler, newCompiler, unixStyle, keepFirstDot ):
        # if the filename is under a ocplUnderscor/ subdirectory then it is copied into a ncplUnderscor/ subdirectory
        # otherwise is copied into a ncplUnderscor file in the same directory

        #fix: automatically get the old compiler
        oldCompiler = DspFile.getCompilerFromName( filename, unixStyle, oldCompiler )

        ( ocpl, ocplUnderscor, ocplSep ) = DspFile.makeCompilerStrings( oldCompiler, unixStyle )
        ( ncpl, ncplUnderscor, ncplSep ) = DspFile.makeCompilerStrings( newCompiler, unixStyle )

        filename = FileUtils.normPath( filename, unixStyle, keepFirstDot )
        fn = filename.lower()

        ocs = ocplSep.lower()

        if ( app.options.enableVcfSpecific ):
            if ( ocpl == compilerVc6 ):
                # the directory is vc60 instead then vc6
                sep = FileUtils.getNormSep( unixStyle )
                ocs = ocpl.lower() + '0' + sep
            if ( newCompiler == compilerVc6 ):
                # the directory is vc60 instead then vc6
                ncplSep = newCompiler + '0' + FileUtils.getNormSep( unixStyle )

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
            so = ocplUnderscor.lower()
            i = bn.find( so )
            if ( i != -1 ):
                lsu = len( so )
                if ( newCompiler != compilerVc6 ):
                    basename = basename[:i] + ncplUnderscor + basename[i+lsu:]
                else:
                    basename = basename[:i] + basename[i+lsu:]
                filename = basename + ext
            else:
                if ( newCompiler != compilerVc6 ):
                    filename = basename + ncplUnderscor + ext

        return filename
    makeDuplicateVcFilename = staticmethod(makeDuplicateVcFilename)

    def duplicateVcDsps( self ):
        # this synchronizes / duplicates vcproj files
        # so *don't* do it for icl7 until it will use vcproj files too

        if ( app.options.copyToIcl7 ):
            self.duplicateVcDspOnly( compilerIcl7 )

        if ( app.options.copyToVc70 ):
            self.duplicateVcDspVcproj( compilerVc70, compilerVc71 )

        if ( app.options.copyToVc71 ):
            self.duplicateVcDspVcproj( compilerVc71, compilerVc70 )

    def duplicateVcDspOnly( self, newCompiler ):
        if ( app.options.enableVcfSpecific ):
            oldFilename = self.filename

            dsp = DspFile( oldFilename )
            newFilenameDsp = dsp.getDuplicateVcFilename( newCompiler, True )
            oldBasenameDsp = os.path.basename( oldFilename )
            newBasenameDsp = os.path.basename( newFilenameDsp )

            dsp.readlines() # first reads the master
            dsp.setFilename( newFilenameDsp )
            dsp.replaceCompilerConfig( newCompiler, False )
            msg = ' duplicated [ %s  -> %s ]' % ( oldBasenameDsp, newBasenameDsp )
            dsp.duplicateVcSaveShowMsg( newFilenameDsp, msg )
        return

    def duplicateVcDspVcproj( self, newCompiler, compilerTryToConvertFrom ):
        # if the vcproj version do not exist then they are not created
        # and the converson proceed from the dsp file only ( synchVcproj = False )
        # If this solution file does *not* exists, then
        #   we first try to create it from the other solution file (
        #     for the version compilerTryToConvertFrom), if it exists
        #   then we synchronize its file list from the dsp file

        if ( app.options.enableVcfSpecific ):
            oldFilename = self.filename

            synchVcproj = False
            synchFromAlt = False
            dsp = DspFile( oldFilename )
            newFilenameDsp = dsp.getDuplicateVcFilename( newCompiler, True )
            oldBasenameDsp = os.path.basename( oldFilename )
            newBasenameDsp = os.path.basename( newFilenameDsp )
            if ( app.options.synchVcprojSln ):
                ( filename, ext ) = os.path.splitext( newFilenameDsp )
                newFilenameVcproj = filename + extVcproj
                newBasenameVcproj = os.path.basename( newFilenameVcproj )
                if ( os.path.exists( newFilenameVcproj ) ):
                    synchVcproj = True
                else:
                    newFilenameVcprojAlt = DspFile.makeDuplicateVcFilename( newFilenameVcproj, newCompiler, compilerTryToConvertFrom, g_internal_unixStyle, True )
                    if ( os.path.exists( newFilenameVcprojAlt ) ):
                        newBasenameVcprojAlt = os.path.basename( newFilenameVcprojAlt )
                        synchVcproj = True
                        synchFromAlt = True
                    else:
                        #else does a copy as dsp just as if ( not app.options.synchVcprojSln )
                        pass

            if ( synchVcproj ):
                if ( app.options.keepDspCopy ):
                    # Keeps or create the dsp 'version' too
                    #if ( 1 < app.options.verbose ):
                    #    print ' duplicating [ %s  -> %s ]' % ( oldBasenameDsp, newBasenameDsp )
                    dsp.readlines() # first reads the master
                    dsp.setFilename( newFilenameDsp )
                    dsp.replaceCompilerConfig( newCompiler, True )
                    msg = ' duplicated [ %s  -> %s ]' % ( oldBasenameDsp, newBasenameDsp )
                    dsp.duplicateVcSaveShowMsg( newFilenameDsp, msg )
                else:
                    #remove dsp 'version' too
                    if ( 1 < app.options.verbose ):
                        print ' removing    [ %s ]' % ( newBasenameDsp )
                    if ( os.path.exists( newFilenameDsp ) ):
                        os.remove( newFilenameDsp )

                if ( synchFromAlt ):
                    #if ( 1 < app.options.verbose ):
                    #    print ' synchr.zing [ %s  -> %s ]' % ( newBasenameVcprojAlt, newBasenameVcproj )
                    dsp = DspFile( oldFilename )
                    dsp.convertVcprojToOtherVersion( newFilenameVcprojAlt, compilerTryToConvertFrom, newCompiler )
                    msg = ' converted [ %s  -> %s ]' % ( newBasenameVcprojAlt, newBasenameVcproj )
                    dsp.setFilename( newFilenameVcproj )
                    dsp.duplicateVcSaveShowMsg( newFilenameVcproj, msg )
                    # and then conform to the dsp

                #if ( 1 < app.options.verbose ):
                #    print ' synchr.zing [ %s  -> %s ]' % ( oldBasenameDsp, newBasenameVcproj )

                dsp = DspFile( oldFilename )
                dsp.setFilename( newFilenameVcproj )
                dsp.conformVcprojLikeDsp( oldFilename, newCompiler ) #%%%%%% uncomment this
                msg = ' updated [ %s  -> %s ]' % ( oldBasenameDsp, newBasenameVcproj )
                dsp.duplicateVcSaveShowMsg( newFilenameVcproj, msg )
            else:
                #if ( 1 < app.options.verbose ):
                #    print ' duplicating [ %s  -> %s ]' % ( oldBasenameDsp, newBasenameDsp )
                dsp.readlines() # first reads the master
                dsp.setFilename( newFilenameDsp )
                dsp.replaceCompilerConfig( newCompiler, False )
                msg = ' duplicated [ %s  -> %s ]' % ( oldBasenameDsp, newBasenameDsp )
                dsp.duplicateVcSaveShowMsg( newFilenameDsp, msg )
        return

    def duplicateVcSaveShowMsg( self, newFilename, msg ):
        self.setFilename( newFilename ) #added just to make sure
        self.saveFile( g_include_vcproj_in_changed_files_counted, app.options.enableProjectFilesModif )
        if ( 1 < app.options.verbose ):
            # we require 1 verbose level more if we modifyVc6
            if ( msg and ( not app.options.modifyVc6 or 2 < app.options.verbose ) ):
                #basename = os.path.basename( oldFilename )
                #print ' duplicated [ %s  -> %s ]' % ( basename, newFilename )
                print msg
        return

    def reformat( self ):
        self.readlines()
        self.process()
        if ( app.options.modifyVc6 ):
            self.saveFile( True, app.options.enableProjectFilesModif )
        return

    def readlines(self):
        fs = file( self.filename, 'r' )

        # Get the new lines
        self.lines = fs.readlines()
        fs.close

    def saveFile( self, count, modify ):
        return self.saveFileContentAs( self.filename, count, modify )

    def saveFileContentAs( self, destination, count, modify ):
        if ( modify ):
            tmpFilename = destination + '.$x$y$'
            #print 'tmpFilename ' + tmpFilename
            if ( os.path.exists( tmpFilename ) ) :
                os.remove( tmpFilename )

            fd = file( tmpFilename, 'w' )
            fd.writelines( self.lines )
            fd.close()

            if ( not os.path.exists( tmpFilename ) ) :
                raise Exception( 'saveFile() - the temporary file \'%s\' had not been created !' % source )

            self.replaceWithFile( tmpFilename, count, modify )

        return

    def replaceWithFile( self, source, count, modify ):
        if ( modify ):
            destination = self.filename

            ( changedFiles, unchangedFiles, createdFiles ) \
                        = FileUtils.replaceFile( source, destination )

            app.changedFilesTot   += changedFiles
            app.unchangedFilesTot += unchangedFiles
            app.createdFilesTot   += createdFiles

            if ( count ):
                app.changedFiles   += changedFiles
                app.unchangedFiles += unchangedFiles
                app.createdFiles   += createdFiles

        return

    pass


################################################################################
class DspGroupData:
    """Structure to hold all the entries for each group (solution explorer folder) of a dsp/vcproj file"""

    # This structure can maybe be eliminated because we changed getSouceEntriesDsp
    # os it uses both this struct and the Vcproj...SectionData structs

    def __init__( self ):
        self.reset()
        return

    def reset( self ):
        #print 'DspGroupData.reset()'
        self.sectionBeforeLines = []
        self.sectionAfterLines = []
        #self.dict = {}
        #self.list = []
        self.groupname = ''
        self.filtervalue = ''
        self.precompheader = ''

        self.listSourceNames = []
        self.dictSourceNames = {}   # dict all sources in the dsp file
        self.dictDspGroupsData = {} # dict all data in a group
        self.dictGroups = {}        # dict all group names in the dsp file
        self.listGroups = []        # list all group names in the dsp file

        # re_dsp_source
        return
    pass

class DspSourceData:
    """Structure to hold all the source entries of a dsp/vcproj file"""
    def __init__( self ):
        self.reset()
        return

    def reset( self ):
        self.dictSourceNames = {}   # dict all sources in the dsp file

        self.dictDspGroupsData = {} # dict all data in a group
        self.dictGroups = {}   # dict all group names in the dsp file
        self.listGroups = []   # list all group names in the dsp file

        self.listGroupNamesConfig   = []
        self.listGroupNamesPlatform = []
        self.listGroupNamesConfigOrPlatform = []
        self.listGroupNamesConfigOrPlatformLwr = []

        self.dictTools = {}         # dict all tools for source files
        self.dictPrecompHeader = {} # dict all precomp header source files ( only one ! )
        self.dictCfgIncludeDir = {} # dict all IncludeLists for all files and Configuration
        self.dictCfgPreprocDef = {} # dict all Preprocessor definitions all files and Configuration

        self.sectionBeforeLines = []
        self.sectionAfterLines = []
        return

    pass

class VcprojGeneralSectionData:
    """Structure to hold all the entries for the general section of a vcproj file"""
    def __init__( self ):
        self.reset()
        return

    def reset( self ):
        self.version_xml = ''
        self.encoding_xml = ''
        self.projectType = ''
        self.version_vc_project = ''
        self.trueProjectName = ''
        #self.sccProjectName = ''
        #self.sccLocalPath = ''
        #self.keyword = ''
        self.platformName = ''

        self.entryNamesList = []
        self.entryNameValueDict = {} # dict of entries for the Config section
        self.configurationFullNamesList = []
        self.configurationsFullNameSectionsDict = {} # dict of all the VcprojConfigSectionData
        return

    def copyHeader( self, src ):
        self.version_xml        = src.version_xml
        self.encoding_xml       = src.encoding_xml
        self.projectType        = src.projectType
        self.version_vc_project = src.version_vc_project
        self.trueProjectName    = src.trueProjectName
        #self.sccProjectName     = src.sccProjectName
        #self.sccLocalPath       = src.sccLocalPath
        #self.keyword            = src.keyword
        self.platformName       = src.platformName
        return

    def copyLists( self, src ):
        self.entryNamesList = src.entryNamesList[:]
        for k, v in src.entryNameValueDict.iteritems():
            self.entryNameValueDict[ k ] = v

        self.configurationFullNamesList = src.configurationFullNamesList[:]
        for k, v in src.configurationsFullNameSectionsDict.iteritems():
            c = VcprojConfigSectionData()
            c.copy( v )
            self.configurationsFullNameSectionsDict[ k ] = c
        return

    def copy( self, src ):
        self.copyHeader( src )
        self.copyLists( src )
        return
    pass

class VcprojConfigSectionData:
    """Structure to hold all the entries for each configuration section of a vcproj file"""
    #           <Configuration
    #                   Name="Debug|Win32"
    #                   OutputDirectory=".\vc71/Debug"
    #                   IntermediateDirectory=".\vc71/Debug"
    #                   ConfigurationType="1"
    #                   UseOfMFC="0"
    #                   ATLMinimizesCRunTimeLibraryUsage="FALSE"
    #                   CharacterSet="2">
    #                   <Tool
    #                   ...>
    def __init__( self ):
        self.reset()
        return

    def reset( self ):
        self.config_name = ''
        self.entryNamesList = []
        self.entryNameValueDict = {} # dict of entries for the Config section
        self.toolNamesList = []
        self.toolNameSectionsDict = {}
        return
    pass

    def copyLists( self, src ):
        self.entryNamesList = src.entryNamesList[:]
        for k, v in src.entryNameValueDict.iteritems():
            self.entryNameValueDict[ k ] = v

        self.toolNamesList = src.toolNamesList[:]
        for k, v in src.toolNameSectionsDict.iteritems():
            c = VcprojToolSectionData()
            c.copy( v )
            self.toolNameSectionsDict[ k ] = c

        return

    def copy( self, src ):
        self.config_name = src.config_name
        self.copyLists( src )
        return

    pass

class VcprojToolSectionData:
    """Structure to hold all the entries for each tool section of a vcproj file"""
    #                                   <Tool
    #                                           Name="VCCLCompilerTool"
    #                                           Optimization="0"
    #                                           AdditionalIncludeDirectories=""
    #                                           PreprocessorDefinitions=""
    #                                           BasicRuntimeChecks="3"/>
    def __init__( self ):
        self.reset()
        return

    def reset( self ):
        self.tool_name = ''
        self.compilerVersion = compilerVersionVc6 # by default well be printed
        self.entryNamesList = []
        self.entryNameValueDict = {} # dict of entries for the Tool section
        return
    pass

    def copyLists( self, src ):
        self.entryNamesList = src.entryNamesList[:]

        for k, v in src.entryNameValueDict.iteritems():
            self.entryNameValueDict[ k ] = v

        return

    def copy( self, src ):
        self.tool_name = src.tool_name
        self.compilerVersion = src.compilerVersion
        self.copyLists( src )
        return

    def appendEntryKeyValue( self, entryKey, entryValue ):
        # this could be static: or member of VcprojToolSectionData
        if ( not self.entryNameValueDict.has_key( entryKey ) ):
            self.entryNamesList.append( entryKey )
            self.entryNameValueDict[ entryKey ] = entryValue
        return

    pass


class VcprojFilterGroupSectionData:
    """Structure to hold all the file sections for each filter/group section of a vcproj file"""
    #           <Filter
    #                   Name="Source Files"
    #                   Filter="cpp;c;cxx;rc;def;r;odl;idl;hpj;bat">
    #                   <File
    #               ...
    #                   </File>
    #           </Filter>
    def __init__( self ):
        self.resetGroups()
        self.isFiles = False
        return

    def resetGroups( self ):
        self.name  = ''
        self.value = ''
        self.level = 0
        self.fileNamesList = []
        self.fileNameFileDict = {} # dict of VcprojFileSectionData
        self.childrenList = []
        self.parent = None
        return

    def copyHierarchy( self, src ):
        self.parent         = src.parent
        self.childrenList   = src.childrenList[:]

        # commented: i.e. shallow copy because the filtergroupNameValueDict will store all the data
        #for ( a, b ) in zip( self.childrenList, src.childrenList ):
        #    a.copy( b )
        #return

    def copyLists( self, src ):
        self.fileNamesList = src.fileNamesList[:]

        for k, v in src.fileNameFileDict.iteritems():
            vcpCfg = VcprojFileSectionData()
            vcpCfg.copy( v )
            self.fileNameFileDict[ k ] = v
        return

    def copy( self, src ):
        self.level      = src.level
        self.name       = src.name
        self.value      = src.value
        self.copyLists( src )
        self.copyHierarchy( src )
        return

    def hasChildren( self ):
        return ( 0 != len( self.childrenList ) )

    def attachAsChildOf( self, parent ):
        self.parent = parent
        if ( parent ):
            parent.childrenList.append( self )

    def attachAsSiblingOf( self, sibling ):
        sibling.parent.childrenList.append( self )
        self.parent = sibling.parent

    def printChildren( self, indent, pretext = '' ):
        if ( self.hasChildren() ):
            for child in self.childrenList:
                print '%s%s [%d] %s   { %d files: %s }' % ( pretext, indent, child.level, child.name, len( child.fileNamesList ), str( child.fileNamesList[:5] ) + '... ' )
                child.printChildren( indent + ' ', pretext )

    pass

class VcprojFilesSectionData( VcprojFilterGroupSectionData ):
    """Structure to hold all the filter/group sections of a vcproj file
        It is derived from VcprojFilterGroupSectionData because it is a very similar container
    """
    #   <Files>
    #           <Filter
    #           ...
    #           </Filter>
    #   </Files>
    def __init__( self ):
        VcprojFilterGroupSectionData.__init__( self )

        #self.morefiles = VcprojFilterGroupSectionData()

        self.resetFiles()

        self.isFiles = True
        return

    def resetFiles( self ):
        self.resetGroups()
        #this is used to allocate memory or the groups
        self.filtergroupNamesList = []
        self.filtergroupNameValueDict = {} # dict of VcprojFilterGroupSectionData
        # this is used for tree recursion
        #self.filtergroupChildrenList = []
        #self.morefiles.reset()
        return

    def copyLists( self, src ):
        # shallow copy
        #self.filtergroupChildrenList = src.filtergroupChildrenList[:]

        self.filtergroupNamesList = src.filtergroupNamesList[:]

        for k, v in src.filtergroupNameValueDict.iteritems():
            c = VcprojFilterGroupSectionData()
            c.copy( v )
            self.filtergroupNameValueDict[ k ] = c
        return

    def copy( self, src ):
        self.copyLists( src )
        VcprojFilterGroupSectionData.copy( self, src )
        return

    def attachChild( self, child ):
        child.parent = self
        self.childrenList.append( child )

    pass

class VcprojFileSectionData:
    """Structure to hold all the files entries for each file section of a vcproj file"""
    #                   <File
    #                           RelativePath=".\Actions.cpp">
    #                           <FileConfiguration
    #                                   Name="Debug|Win32">
    #                                   <Tool
    #                                   ...>
    #                           </FileConfiguration>
    #                           <FileConfiguration
    #                                   Name="Release|Win32">
    #                                   <Tool
    #                                   ...>
    #                           </FileConfiguration>
    #                   </File>
    def __init__( self ):
        self.reset()
        return

    def reset( self ):
        self.file_name = ''
        self.file_relativepath = ''
        self.fileConfigNamesList = []
        self.fileConfigNameSectionsDict = {} # dict of all VcprojFileConfigurationSectionData
        return
    pass

    def copyLists( self, src ):
        self.fileConfigNamesList = src.fileConfigNamesList[:]
        for k, v in src.fileConfigNameSectionsDict.iteritems():
            vcpCfg = VcprojFileConfigurationSectionData()
            vcpCfg.copy( v )
            self.fileConfigNameSectionsDict[ k ] = v
        return

    def copy( self, src ):
        self.file_name = ''
        self.file_relativepath = src.file_relativepath
        self.copyLists( src )
        return
    pass

class VcprojFileConfigurationSectionData:
    """Structure to hold all the entries for each FileConfiguration of each File section of a vcproj file"""
    #                   <File
    #                           RelativePath=".\Actions.cpp">
    #                           <FileConfiguration
    #                                   Name="Debug|Win32">
    #                                   <Tool
    #                                           ...>
    #                                   <Tool
    #                                           ...>
    #                           </FileConfiguration>
    #                   </File>
    def __init__( self ):
        self.reset()
        return

    def reset( self ):
        self.fileConfig_name = ''
        self.toolNamesList = []
        self.toolNameSectionsDict = {} # dict of all VcprojToolSectionData
        return
    pass

    def copyLists( self, src ):
        self.toolNamesList = src.toolNamesList[:]
        for k, v in src.toolNameSectionsDict.iteritems():
            vcpCfg = VcprojToolSectionData()
            vcpCfg.copy( v )
            self.toolNameSectionsDict[ k ] = v
        return

    def copy( self, src ):
        self.fileConfig_name = src.fileConfig_name
        self.copyLists( src )
        return
    pass

class DspFile( GenericProjectFile ):
    """Process and reformat dsp files as in Visual Studio 6."""

    def __init__( self, filename ):
        GenericProjectFile.__init__( self, filename )

        self.resetDspFile()
        pass

    def __del__(self):
        #print "del DspFile"
        pass

    def resetDspFile( self ):
        self.optionsDict = {}

        self.dictSourceNames = {}   # dict all sources in the dsp file

        self.dictDspGroupsData = {} # dict all data in a group
        self.dictGroups = {}   # dict all group names in the dsp file
        self.listGroups = []   # list all group names in the dsp file

        self.listGroupNamesConfig   = []
        self.listGroupNamesPlatform = []
        self.listGroupNamesConfigOrPlatform = []
        self.listGroupNamesConfigOrPlatformLwr = []

        self.dictTools = {}         # dict all tools for source files
        self.dictPrecompHeader = {} # dict all precomp header source files ( only one ! )
        self.dictCfgIncludeDir = {} # dict all IncludeLists for all files and Configuration
        self.dictCfgPreprocDef = {} # dict all Preprocessor definitions all files and Configuration

        self.sectionBeforeLines = []
        self.sectionAfterLines = []

        return

    def reformat( self ):
        self.readlines()
        self.process()
        if ( app.options.modifyVc6 ):
            self.saveFile( True, app.options.enableProjectFilesModif )
        return

    def replaceCompilerConfig( self, newCompiler, onlyInsideConfig ):
        # replaces the entries oldcompiler --> newcompiler only inside the configurations section of a dsp file
        insideCfg = False
        self.nCfg = -1

        insideCfg = False
        if ( not onlyInsideConfig ):
            insideCfg = True

        ( ocpl, ocplUnderscor, ocplSep ) = DspFile.makeCompilerStrings( self.compiler, g_internal_unixStyle )
        ( ncpl, ncplUnderscor, ncplSep ) = DspFile.makeCompilerStrings( newCompiler  , g_internal_unixStyle )

        sep1 = FileUtils.getNormSep( False )
        sep2 = FileUtils.getNormSep( True )
        ocplSep1 = self.compiler + sep1
        ncplSep1 = newCompiler + sep1
        ocplSep2 = self.compiler + sep2
        ncplSep2 = newCompiler + sep2

        if ( app.options.enableVcfSpecific ):
            #if ( ocpl == compilerVc6 ):
            #    # the directory is vc60 instead then vc6
            #    ocs = ocpl.lower() + '0' + sep
            if ( ocpl == compilerVc6 ):
                ocplSep1 = self.compiler + '0' + sep1
                ocplSep2 = self.compiler + '0' + sep2
                ocplSep1FixProblem = self.compiler + sep1
                ocplSep2FixProblem = self.compiler + sep2

            if ( newCompiler == compilerVc6 ):
                # the directory is vc60 instead then vc6
                #ncplSep = newCompiler + '0' + FileUtils.getNormSep( g_internal_unixStyle )
                ncplSep1 = newCompiler + '0' + sep1
                ncplSep2 = newCompiler + '0' + sep2

        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n + 1

            #* exit after end of CFG section
            if ( not onlyInsideConfig and line.find( '# Begin Target' ) != -1 ):
                insideCfg = False
                break

            if ( onlyInsideConfig ):
                if ( line[0] == '!' ):
                    m = re_configuration.match( line )
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

                chg = True
                while ( chg ):
                    chg = False

                    # we don't know if the line will be using 'compiler/' or 'compiler\'
                    i = line.find( ocplSep1 )
                    if ( i != -1 ):
                        ocplSepLen = len( ocplSep1 )
                        line = line[:i] + ncplSep1 + line[i+ocplSepLen:]
                        changed = True
                        chg = True

                    i = line.find( ocplSep2 )
                    if ( i != -1 ):
                        ocplSepLen = len( ocplSep2 )
                        line = line[:i] + ncplSep2 + line[i+ocplSepLen:]
                        changed = True
                        chg = True

                    if ( ocpl == compilerVc6 ):
                        i = line.find( ocplSep1FixProblem )
                        if ( i != -1 ):
                            ocplSepLen = len( ocplSep1FixProblem )
                            line = line[:i] + ncplSep1 + line[i+ocplSepLen:]
                            changed = True
                            chg = True

                        i = line.find( ocplSep2FixProblem )
                        if ( i != -1 ):
                            ocplSepLen = len( ocplSep2FixProblem )
                            line = line[:i] + ncplSep2 + line[i+ocplSepLen:]
                            changed = True
                            chg = True


                if ( changed ):
                    self.lines[n] = line # apply changes

        return

    def replaceCompilerTextMakeTuple( oldCompiler, newCompiler ):
        ( ocpl, ocplUnderscor, ocplSep ) = DspFile.makeCompilerStrings( oldCompiler, g_internal_unixStyle )
        ( ncpl, ncplUnderscor, ncplSep ) = DspFile.makeCompilerStrings( newCompiler  , g_internal_unixStyle )

        sep1 = FileUtils.getNormSep( False )
        sep2 = FileUtils.getNormSep( True )
        ocplSep1 = oldCompiler + sep1
        ncplSep1 = newCompiler + sep1
        ocplSep2 = oldCompiler + sep2
        ncplSep2 = newCompiler + sep2

        if ( app.options.enableVcfSpecific ):
            #if ( ocpl == compilerVc6 ):
            #    # the directory is vc60 instead then vc6
            #    ocs = ocpl.lower() + '0' + sep
            if ( ocpl == compilerVc6 ):
                ocplSep1 = oldCompiler + '0' + sep1
                ocplSep2 = oldCompiler + '0' + sep2
                #ocplSep1FixProblem = oldCompiler + sep1
                #ocplSep2FixProblem = oldCompiler + sep2

            if ( newCompiler == compilerVc6 ):
                # the directory is vc60 instead then vc6
                #ncplSep = newCompiler + '0' + FileUtils.getNormSep( g_internal_unixStyle )
                ncplSep1 = newCompiler + '0' + sep1
                ncplSep2 = newCompiler + '0' + sep2

        ocplUnderscorLen = len( ocplUnderscor )
        ocpl1SepLen = len( ocplSep1 )
        ocpl2SepLen = len( ocplSep2 )
        #ocpl1SepFixLen = len( ocplSep1FixProblem )
        #ocpl2SepFixLen = len( ocplSep2FixProblem )

        #replaceCompilerTuple = ( (  ocplUnderscor, ocplUnderscorLen, ncplUnderscor ), ( ocpl1SepLen, ocpl1SepFixLen, ocpl2SepLen, ocpl2SepFixLen ), \
        #                        ( ocplSep1, ocplSep1FixProblem, ncplSep1 ), ( ocplSep2, ocplSep2FixProblem, ncplSep2 ) )
        replaceCompilerTuple = ( (oldCompiler, newCompiler), (  ocplUnderscor, ocplUnderscorLen, ncplUnderscor ), ( ocpl1SepLen, ocpl2SepLen ), \
                                ( ocplSep1, ncplSep1 ), ( ocplSep2, ncplSep2 ) )
        return replaceCompilerTuple
    replaceCompilerTextMakeTuple = staticmethod(replaceCompilerTextMakeTuple)

    def replaceCompilerTextTuple( text, replaceCompilerTuple ):
        #( (  ocplUnderscor, ocplUnderscorLen ), ( ocpl1SepLen, ocpl1SepFixLen, ocpl2SepLen, ocpl2SepFixLen ), \
        #  ( ocplSep1, ocplSep1FixProblem, ncplSep1 ), ( ocplSep2, ocplSep2FixProblem, ncplSep2 ) ) = replaceCompilerTuple
        ( (oldCompiler, newCompiler), (  ocplUnderscor, ocplUnderscorLen, ncplUnderscor ), ( ocpl1SepLen, ocpl2SepLen ), \
          ( ocplSep1, ncplSep1 ), ( ocplSep2, ncplSep2 ) ) = replaceCompilerTuple

        # very slow function. We can think of speeding it up if necessary
        # buy just providing all the ( ocpl, ocplUnderscor, ocplSep ) crap

        # replaces the entries oldcompiler --> newcompiler only inside the configurations section of a dsp file

        if ( oldCompiler == newCompiler ):
            return text

        changed = False
        i = 0
        while ( i != -1 ):
            i = text.find( ocplUnderscor )
            if ( i != -1 ):
                text = text[:i] + ncplUnderscor + text[i+ocplUnderscorLen:]
                changed = True

        chg = True
        while ( chg ):
            chg = False

            # we don't know if the text will be using 'compiler/' or 'compiler\'
            i = text.find( ocplSep1 )
            if ( i != -1 ):
                text = text[:i] + ncplSep1 + text[i+ocpl1SepLen:]
                changed = True
                chg = True

            i = text.find( ocplSep2 )
            if ( i != -1 ):
                text = text[:i] + ncplSep2 + text[i+ocpl2SepLen:]
                changed = True
                chg = True

            #if ( ocpl == compilerVc6 ):
            #    i = text.find( ocplSep1FixProblem )
            #    if ( i != -1 ):
            #        text = text[:i] + ncplSep1 + text[i+ocpl1SepFixLen:]
            #        changed = True
            #        chg = True
            #
            #    i = text.find( ocplSep2FixProblem )
            #    if ( i != -1 ):
            #        text = text[:i] + ncplSep2 + text[i+ocpl2SepFixLen:]
            #        changed = True
            #        chg = True

        return text
    replaceCompilerTextTuple = staticmethod(replaceCompilerTextTuple)

    def replaceCompilersText( text, newCompiler ):
        # brute force
        text = text.replace( compilerVc6 , newCompiler )
        text = text.replace( compilerIcl7, newCompiler )
        text = text.replace( compilerVc70, newCompiler )
        text = text.replace( compilerVc71, newCompiler )
        return text
    replaceCompilersText = staticmethod(replaceCompilersText)

    def readTargetSection( self ):
        # skips all the configuration lines and copy all the target body into a string

        targetSection = ''
        state = 0
        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n + 1

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
            self.n = n + 1


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

        if ( app.options.enableProjectFilesModif ):
            if ( os.path.exists( tmpFilename ) ) :
                os.remove( tmpFilename )

            fd = file( tmpFilename, 'w' )
            fd.writelines( configurationSection )
            fd.writelines( targetSection )
            fd.close()

            if ( not os.path.exists( tmpFilename ) ) :
                raise Exception( 'replaceTarget() - the temporary file \'%s\' had not been created !' % tmpFilename )

        return tmpFilename

    def getProjectInfos( self, trySlnFirst, knownUuid = '' ):
        # Note[*]: this function is fully implemented,
        # but the function self.getProjectInfosVcproj is not yet
        # To start from the dps it is also usually better because
        # vc6 is the basis for vcf ( we can change this in the futer by just uncommenting the
        # following statement and implementing self.getProjectInfosVcproj
        # So we set:
        trySlnFirst = False

        # first tries to open the vcproj file
        found = False
        if ( trySlnFirst ):
            newFilename = self.filename
            ( root, ext ) = os.path.splitext( self.filename )
            newFilename = root + extVcproj
            compiler = compilerVc70
            newFilename = DspFile.makeDuplicateVcFilename( newFilename, compilerVc6, compiler, g_internal_unixStyle, True )
            if ( not os.path.exists( newFilename ) ):
                compiler = compilerVc71
                newFilename = DspFile.makeDuplicateVcFilename( newFilename, compilerVc6, compiler, g_internal_unixStyle, True )
                if ( os.path.exists( newFilename ) ):
                    found = True
            else:
                found = True

            if ( found ):
                #dspFile = DspFile( prjpath )
                self.setFilename( newFilename )
                #self.setName( newFilename )
                self.setCompilerStrings( compiler )
                slnPrjData = self.getProjectInfosVcproj( compiler, knownUuid )
            else:
                trySlnFirst = False

        if ( not trySlnFirst ):
            newFilename = self.filename
            ( root, ext ) = os.path.splitext( self.filename )
            newFilename = root + extDsp
            compiler = compilerVc6
            # improve this !
            newFilename = DspFile.makeDuplicateVcFilename( newFilename, compilerVc6, compilerVc6, g_internal_unixStyle, True )
            if ( not os.path.exists( newFilename ) ):
                raise Exception( 'DspFile.getProjectInfos: unable to find the project \'%s\' !' % newFilename )

            self.setFilename( newFilename )
            #self.setName( newFilename )
            self.setCompilerStrings( compiler )
            self.readlines()
            slnPrjData = self.getProjectInfosDsp( compiler, knownUuid )

        return slnPrjData

    def getProjectInfosDsp( self, compiler, knownUuid = '' ):
        # reads the cfg infos from a dsp file
        # read all the configuration lines and copy them all into a string

        slnPrjData = SlnProjectData()

        state = 0
        trueProjectName = ''
        projectType = ''
        outputExt = ''
        appType = enumAppTypeNone

        insideCfg = True
        nCfg = -1
        projectName = ''
        platform    = ''
        platformList = []
        configFullName  = ''
        configFullNameList = []
        configName  = ''
        configNameList = []
        configOrPlatformName = ''
        configOrPlatformNameList = []
        configFullNameExCfgPlatfAssocDict = {}

        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n + 1

            if ( state == 0 ):
                # Microsoft Developer Studio Project File - Name="ApplicationKitDLL" - Package Owner=<4>
                m_trueproject = re_trueproject.match( line )
                if ( m_trueproject ):
                    trueProjectName = m_trueproject.group('trueProjectName')
                    trueProjectNameLwr = self.trueProjectName.lower()
                    if ( trueProjectNameLwr.find( 'wiz' ) != -1 or trueProjectNameLwr.find( 'ins' ) != -1 ):
                        msg = 'getOutputTypeAndDir: this application [%s] is probably an addins. File \'%s\' (%d). Line \'%s\'' % ( self.trueProjectName, self.filename, self.n, line.rstrip() )
                        self.isAddins = True
                        #print msg
                        #raise Exception( msg )
                    continue

                # TARGTYPE "Win32 (x86) Static Library" 0x0104
                m_targettype = re_targettype.match( line )
                if ( m_targettype ):
                    #Microsoft made this not working either: a dll can have 'Application' as projectType see ImageFormats !
                    # fortunately it doesn't really matters !
                    if ( False ):
                        projectType = m_targettype.group( r'projectType' )
                        projectTypeLwr = projectType.lower()

                        if ( projectTypeLwr == 'generic project' ):
                            # this type has no output: is just a project to compile all its dependencies
                            outputExt = '.generic'
                            appType = enumAppTypeGeneric
                        elif ( projectTypeLwr == 'application' ):
                            outputExt = '.exe'
                            appType = enumAppTypeExe
                        elif ( projectTypeLwr == 'console application' ):
                            outputExt = '.exe'
                            appType = enumAppTypeExe
                        elif ( projectTypeLwr == 'static library' ):
                            outputExt = '.lib'
                            appType = enumAppTypeLib
                        elif ( projectTypeLwr == 'dynamic-link library' ):
                            outputExt = '.dll'
                            appType = enumAppTypeDll
                        elif ( projectTypeLwr == 'add-ins' ):
                            outputExt = '.awx'
                        else:
                            raise Exception( 'getProjectInfosDsp: unknow project type [%s]. File \'%s\'. Line \'%s\'' % ( projectType, self.filename, line ) )
                        pass
                    state = 1
                    continue


            elif ( state == 1 ):
                #!IF  "$(CFG)" == "libAGG - Win32 GTK Debug"
                if ( line[0] == '!' ):
                    m_configuration = re_configuration.search( line )
                    if ( m_configuration ):
                        insideCfg = True
                        nCfg += 1
                        projectName = m_configuration.group('projectName')
                        platform    = m_configuration.group('platform').rstrip() # we don't really need it
                        platformList.append( platform )
                        configFullName  = m_configuration.group('configFullName')
                        configFullNameList.append( configFullName ) # 'GTK Debug'
                        #m_confignamesplit = re_confignamesplit.match( configFullName )
                        #if ( m_confignamesplit ):
                        configFullNameList.append( configFullName )
                        if ( configFullName ):
                            splitlist = configFullName.split()
                            if ( 1 < len( splitlist ) ):
                                configName = ' '.join( splitlist[1:] )
                            else:
                                configName = configFullName
                            configNameList.append( configName )
                            configNameList.append( configName )
                            configOrPlatformName = '%s|%s' % ( configFullName, platform )
                            configOrPlatformNameList.append( configOrPlatformName )

                            configFullNameExCfgPlatfAssocDict[ configFullName ] = configOrPlatformName
                        else:
                            raise Exception( 'getOutputTypeAndDir: unable to split the configFullName (%s) in its parts )' % self.configFullName )

                        #m_confignamesplit = re_confignamesplit.match( configFullName )
                        #if ( m_confignamesplit ):
                        #    configName  = m_confignamesplit.group('configName')
                        #    configNameList.append( configName )
                        #    configOrPlatformName = '%s|%s' % ( configFullName, platform )
                        #    configOrPlatformNameList.append( configOrPlatformName )
                        #    configFullNameExCfgPlatfAssocDict[ configFullName ] = configOrPlatformName
                        #else:
                        #    raise Exception( 'getOutputTypeAndDir: unable to split the configFullName (%s) in its parts )' % configFullName )
                        continue

                if ( re.match( '# Begin Target', line ) ):
                    state = 2

            elif ( state == 2 ):
                break

            else:
                pass

        if ( state != 2 ):
            raise Exception( 'wrong final state: [%d]. Read %d lines in \'%s\'' % ( state, self.n, self.filename ) )

        slnPrjData.prjName = projectName
        slnPrjData.prjAbsPath = self.filename
        if ( knownUuid ):
            slnPrjData.prjUuid = knownUuid
        else:
            slnPrjData.prjUuid = app.getNextUuid( projectName )
        slnPrjData.prjConfigFullNameList = configFullNameList
        slnPrjData.prjConfigNameList = configNameList
        slnPrjData.prjPlatformNameList = platformList
        slnPrjData.prjConfigOrPlatformNameList = configOrPlatformNameList
        slnPrjData.prjConfigFullNameExCfgPlatfAssocDict = configFullNameExCfgPlatfAssocDict
        #if ( projectName == 'libAGG' ):
        #x = mom

        return slnPrjData

    def getProjectInfosVcproj( self, trySlnFirst, knownUuid = '' ):
        # reads the cfg infos from a vcproj file
        raise Exception( 'getProjectInfosVcproj: not implemented yet for vcprojs' )

        slnPrjData = SlnProjectData()

        state = 0
        trueProjectName = ''
        projectType = ''
        outputExt = ''
        appType = enumAppTypeNone

        insideCfg = True
        nCfg = -1
        projectName = ''
        platform    = ''
        platformList = []
        configFullName  = ''
        configFullNameList = []
        configName  = ''
        configNameList = []
        configOrPlatformName = ''
        configOrPlatformNameList = []
        configFullNameExCfgPlatfAssocDict = {}

        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n + 1

            if ( state == 0 ):
                pass

            elif ( state == 2 ):
                break

            else:
                pass

        if ( state != 2 ):
            raise Exception( 'wrong final state: [%d]. Read %d lines in \'%s\'' % ( state, self.n, self.filename ) )

        slnPrjData.prjName = projectName
        slnPrjData.prjAbsPath = self.filename
        slnPrjData.prjUuid = app.getNextUuid( projectName )
        slnPrjData.prjConfigFullNameList = configFullNameList # 'GTK Debug'
        slnPrjData.prjConfigNameList = configNameList
        slnPrjData.prjPlatformNameList = platformList
        slnPrjData.prjConfigOrPlatformNameList = configOrPlatformNameList
        slnPrjData.prjConfigFullNameExCfgPlatfAssocDict = configFullNameExCfgPlatfAssocDict

        return slnPrjData

    def conformVcprojLikeDsp( self, filenameDsp, newCompiler ):
        # keeps the configuration section unchanged,
        # but it creates all the project entries

        # read the dsp file
        dsp = DspFile( filenameDsp )
        vcpFilesDsp = dsp.readSouceEntriesDsp()

        # now read the vcproj file
        ( vcpHdr, vcpFilesOrg ) = self.readEntriesVcproj( newCompiler )

        #if ( oldCompiler != newCompiler ):
        #    ( vcpHdr, vcpFilesOrg ) = self.convertEntriesVcproj( vcpHdr, vcpFilesOrg, oldCompiler, newCompiler )

        # reformat the current project in a 'standard' way
        # if it doesn't seem to work, please look into convertEntriesVcproj and see if
        # we used just g_KeepFirstDot_True instead than g_KeepFirstDot_Add
        ( vcpHdr, vcpFilesOrg ) = self.convertEntriesVcproj( vcpHdr, vcpFilesOrg, newCompiler, newCompiler )

        if ( g_printFilterGroupTrees and self.isFileIn2() ):
            vcpFilesDsp.printChildren( '.', 'vcpFilesDsp' )
            vcpFilesOrg.printChildren( ' ', 'vcpFilesOrg' )
            print 'now writelineEntriesVcprojAsStruct:\n'

        # this automatically 'converts' to the newCompiler if the entries exist
        self.writelineEntriesVcprojAsStruct( vcpHdr, vcpFilesDsp, newCompiler, vcpFilesOrg )

        return

    def convertVcprojToOtherVersion( self, oldFilenameVcproj, oldCompiler, newCompiler ):
        self.setFilename( oldFilenameVcproj )
        oldBasenameVcproj = os.path.basename( oldFilenameVcproj )

        newFilenameVcproj = DspFile.makeDuplicateVcFilename( oldFilenameVcproj, oldCompiler, newCompiler, g_internal_unixStyle, True )
        newBasenameVcproj = os.path.basename( newFilenameVcproj )

        if ( 0 <= app.options.verbose ):
            print ' converting [ %s  -> %s ]' % ( oldBasenameVcproj, newBasenameVcproj )

        self.convertVcproj( oldCompiler, newCompiler )

        self.setFilename( newFilenameVcproj )

        return

    def removeSccLinesVcproj( self, compiler ):
        self.readlines()

        # this has just the effect of removing the unwanted Scc lines
        convertVcproj( self, compiler, compiler )

        return

    def convertVcproj( self, oldCompiler, newCompiler ):
        self.readlines()

        #if ( reset ):
        #    self.resetDspFile()

        ( vcpHdr, vcpFiles ) = self.getEntriesVcproj( oldCompiler, False )

        if ( oldCompiler != newCompiler ):
            ( vcpHdr, vcpFiles ) = self.convertEntriesVcproj( vcpHdr, vcpFiles, oldCompiler, newCompiler )

        # this automatically 'converts' to the newCompiler if the entry exists
        self.writelineEntriesVcprojAsStruct( vcpHdr, vcpFiles, newCompiler )

        return

    def readSouceEntriesDsp( self ):
        self.readlines()
        vcpFiles = self.getSouceEntriesDsp()
        return vcpFiles

    def getSouceEntriesDsp( self ):
        state = 0

        self.resetDspFile()

        c_None               = 0
        c_FilterGroupSection = 1
        c_FileSection        = 2
        c_FileConfigSection  = 3
        c_ToolSection        = 4

        vcpFiles = VcprojFilesSectionData()

        isKey = c_None
        insideFileSection = False

        groupname = ''
        c_InitialLevel = 0
        level = c_InitialLevel
        fgIdx = -1
        previousFilterGroup = None

        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n + 1

            # skips the configurations body but save it into sectionBeforeLines
            if ( state == 0 ):
                self.sectionBeforeLines.append( line )

                # Begin Target
                if ( re.match( '# Begin Target', line ) ):
                    #vcpFiles = VcprojFilesSectionData()
                    state = 1

            elif ( state == 1 ):
                # Name "ApplicationKitDLL - Win32 Release"
                # Name "ApplicationKitDLL - Win32 Debug"
                m_dsp_group_name_basic = re_dsp_group_name_basic.match( line )
                if ( m_dsp_group_name_basic ):
                    m_dsp_group_name = re_dsp_group_name.match( line )
                    if ( m_dsp_group_name ):
                        platform = m_dsp_group_name.group( 'platform' )
                        configName = m_dsp_group_name.group( 'configName' )
                        self.listGroupNamesPlatform.append( platform )
                        self.listGroupNamesConfig.append( configName )
                        configOrPlatform = '%s|%s' % ( configName, platform )
                        self.listGroupNamesConfigOrPlatform.append( configOrPlatform )
                        self.listGroupNamesConfigOrPlatformLwr.append( configOrPlatform.lower() )
                    else:
                        raise Exception( 'getSouceEntriesDsp: reading name but not name + infos. File: \'%s\'. Line[%d]: \'%s\'' % ( self.filename, self.n, line.rstrip() ) )
                    continue

                # Begin Group "Header Files"
                m_dsp_group_basic_beg = re_dsp_group_basic_beg.match( line )
                if ( m_dsp_group_basic_beg ):
                    m_dsp_group = re_dsp_group.match( line )
                    if ( m_dsp_group ):
                        # to increment the level here or at the end of this function is pretty much the same thing
                        level = level + 1

                        dspData = DspGroupData()
                        groupname = m_dsp_group.group( 'groupname' )
                        dspData.groupname = groupname

                        if ( 0 <= fgIdx ):
                            previousFilterGroup = vcpFiltergrp

                        # new FilterGroup data
                        vcpFiltergrp = VcprojFilterGroupSectionData()
                        vcpFiltergrp.name = groupname
                        vcpFiltergrp.level = level

                        if ( c_InitialLevel + 1 == level ):
                            vcpFiles.attachChild( vcpFiltergrp )
                        else:
                            if ( previousFilterGroup.level < level ):
                                vcpFiltergrp.attachAsChildOf( previousFilterGroup )
                            else:
                                vcpFiltergrp.attachAsSiblingOf( previousFilterGroup )

                        # store it immediately: it is a queue. So the order is preserved!
                        vcpFiles.filtergroupNamesList.append( vcpFiltergrp.name )
                        fgIdx = fgIdx + 1
                        vcpFiles.filtergroupNameValueDict[ vcpFiltergrp.name.lower() ] = vcpFiltergrp

                        if ( g_printFilterGroupTrees and self.isFileIn2() ):
                            print 'getSouceEntriesDsp: file: %s' % self.filetitle
                            vcpFiles.printChildren( '.', 'vcpFiles' )

                    else:
                        raise Exception( 'getSouceEntriesDsp: reading group but not group + infos. File: \'%s\'. Line[%d]: \'%s\'' % ( self.filename, self.n, line.rstrip() ) )
                    continue

                # # End Group
                m_dsp_group_basic_end = re_dsp_group_basic_end.match( line )
                if ( m_dsp_group_basic_end ):
                    if ( groupname ):
                        #save previous data
                        groupnameLwr = groupname.lower()
                        self.dictDspGroupsData[ groupnameLwr ] = dspData
                        self.listGroups.append( groupname )
                        self.dictGroups[ groupnameLwr ] = groupname

                        # for the other <file>s still to attach or whatever sub filter we have
                        # the 'current group is now the parent one !
                        vcpFiltergrp = vcpFiltergrp.parent

                        # at the end becase += 1 is done at the beginning of the <Filter management
                        level = level - 1
                    continue


                # # PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
                m_dsp_filter_basic = re_dsp_filter_basic.match( line )
                if ( m_dsp_filter_basic ):
                    m_dsp_filter = re_dsp_filter.match( line )
                    if ( m_dsp_filter ):
                        dspData.filtervalue = m_dsp_filter.group( 'filtervalue' )
                        vcpFiltergrp.value = dspData.filtervalue
                    else:
                        raise Exception( 'getSouceEntriesDsp: reading filter but not filter + infos. File: \'%s\'. Line[%d]: \'%s\'' % ( self.filename, self.n, line.rstrip() ) )
                    continue

                # # Begin Source File
                m_dsp_src_file_beg = re_dsp_src_file_beg.match( line )
                if ( m_dsp_src_file_beg ):
                    # new File data
                    vcpFile = VcprojFileSectionData()
                    isKey = c_FileSection # 2
                    insideFileSection = True
                    continue

                # # End Source File
                m_dsp_src_file_end = re_dsp_src_file_end.match( line )
                if ( m_dsp_src_file_end ):
                    if ( 0 == level ):
                        container = vcpFiles
                    else:
                        container = vcpFiltergrp

                    container.fileNamesList.append( vcpFile.file_name ) # we know that they are unique
                    filenameLwr = vcpFile.file_name.lower()
                    if ( container.fileNameFileDict.has_key( filenameLwr ) ):
                        raise Exception( 'getSouceEntriesDsp: The file \'%s\' already exists in this FilterGroup section [%s]. File \'%s\' (%d). Line \'%s\'' % ( vcpFile.file_name, container.name, self.filetitle, self.n, line.rstrip() ) )
                    container.fileNameFileDict[ filenameLwr ] = vcpFile

                    insideFileSection = False
                    continue

                # SOURCE=..\FreeImage\BitmapAccess.cpp
                m_dsp_source_basic = re_dsp_source_basic.match( line )
                if ( m_dsp_source_basic ):
                    m_dsp_source = re_dsp_source.match( line )
                    if ( m_dsp_source ):
                        source = m_dsp_source.group( 'sourcename' )
                        source = FileUtils.normPath( source, g_internal_unixStyle )
                        dspData.listSourceNames.append( source )

                        basename = os.path.basename( source )
                        basenameLwr = basename.lower()
                        dspData.dictSourceNames[ basenameLwr ] = source
                        self.dictSourceNames[ basenameLwr ] = source

                        vcpFile.file_relativepath = source
                        vcpFile.file_name = basename

                        isKey = c_FileSection
                    else:
                        raise Exception( 'getSouceEntriesDsp: reading source but not source + infos. File: \'%s\'. Line[%d]: \'%s\'' % ( self.filename, self.n, line.rstrip() ) )
                    continue

                #m_dsp_useprecompheader_c = re_dsp_useprecompheader_c.search( line )
                #if ( m_dsp_useprecompheader_c ):
                #    precompHeader = m_dsp_useprecompheader_c.group( 'precompheader' )
                #    self.dictPrecompHeader[  basenameLwr ] = precompHeader
                #    continue


                if ( insideFileSection ):
                    #!IF  "$(CFG)" == "libAGG - Win32 GTK Debug"
                    if ( line[0] == '!' ) :
                        # !IF  "$(CFG)" == "ApplicationKitDLL - Win32 Release"
                        # # ADD CPP /Yu
                        # !ELSEIF  "$(CFG)" == "ApplicationKitDLL - Win32 Debug"
                        # # ADD CPP /Yu
                        # !ENDIF
                        m_configuration = re_configuration.match( line )
                        if ( m_configuration ):
                            insideCfg = True
                            projectName = m_configuration.group('projectName')
                            platform    = m_configuration.group('platform').rstrip()  # we don't really need it
                            configFullName  = m_configuration.group('configFullName') # GTK Debug

                            if ( configFullName ):
                                splitlist = configFullName.split()
                                if ( 1 < len( splitlist ) ):
                                    configName = ' '.join( splitlist[1:] )
                                else:
                                    configName = configFullName
                                configNamePlatform = '%s|%s' % ( configFullName, platform )
                            else:
                                raise Exception( 'getSouceEntriesDsp: unable to split the configFullName (%s) in its parts )' % self.configFullName )

                            # new FileConfiguration data: we can add them at the beginning because they are pointers
                            vcpFilecfg = VcprojFileConfigurationSectionData()
                            vcpFilecfg.fileConfig_name = configNamePlatform
                            vcpFile.fileConfigNamesList.append( vcpFilecfg.fileConfig_name )
                            fileConfig_nameLwr = vcpFilecfg.fileConfig_name.lower()
                            vcpFile.fileConfigNameSectionsDict[ fileConfig_nameLwr ] = vcpFilecfg
                            continue

                        m_configuration_endif = re_configuration_endif.match( line )
                        if ( m_configuration_endif ):
                            continue

                        m_ADD_CPP = re_ADD_CPP.match( line )
                        if ( m_ADD_CPP ):
                            vcpTool = VcprojToolSectionData()
                            vcpTool.tool_name = VCCLCompilerTool

                            # we only need to look for precompiled header for now
                            m_dsp_useprecompheader_c = re_dsp_useprecompheader_c.search( line )
                            if ( m_dsp_useprecompheader_c ):
                                precompHeader = m_dsp_useprecompheader_c.group( 'precompheader' )
                                self.dictPrecompHeader[  basenameLwr ] = precompHeader
                                #PrecompiledHeaderThrough="ApplicationKit.h"
                                #PrecompiledHeaderFile=".\vc71/ReleaseS/ApplicationKit_vc71.pch"
                                continue

                            # we only need to look for precompiled header for now
                            m_dsp_useprecompheader_u = re_dsp_useprecompheader_u.search( line )
                            if ( m_dsp_useprecompheader_u ):
                                precompHeader = m_dsp_useprecompheader_u.group( 'precompheader' )
                                #UsePrecompiledHeader="1"/
                                vcpTool.entryNamesList.append( 'UsePrecompiledHeader' )
                                vcpTool.entryNameValueDict[ entryName ] = '\"1\"'
                                continue

                            vcpFilecfg.toolNamesList.append( vcpTool.tool_name )
                            vcpFilecfg.toolNameSectionsDict[ vcpTool.tool_name ] = vcpTool

                        m_PROP = re_PROP.match( line )
                        if ( m_PROP ):
                            pass

                        m_custom_build_beg = re_custom_build_beg.amtch( line )
                        if ( m_custom_build_beg ):
                            pass

                        m_custom_build_end = re_custom_build_end.amtch( line )
                        if ( m_custom_build_end ):
                            pass

                # End Project
                if ( re.match( '# End Project', line ) ):
                    if ( groupname ):
                        #save previous data
                        groupnameLwr = groupname.lower()
                        self.dictDspGroupsData[ groupnameLwr ] = dspData

                    if ( 0 != level ):
                        msg = 'getSouceEntriesDsp: ***ERROR*** completed but the level is not null [%d]. File \'%s\' ' % ( level, self.filename )
                        print( msg )
                        #raise Exception( msg )

                    state = 2
                    continue
            else:
                pass

        if ( state != 2 ):
            raise Exception( 'getSouceEntriesDsp: wrong final state: [%d]. Read %d lines in \'%s\'' % ( state, self.n, self.filename ) )

        return vcpFiles

    def readEntriesVcproj( self, compiler ): # reset = False
        #if ( reset ):
        #    self.resetDspFile()

        self.readlines()

        ( vcpHdr, vcpFiles ) = self.getEntriesVcproj( compiler )

        return  ( vcpHdr, vcpFiles )

    def getEntriesVcproj( self, compiler, reset = False ):
        state = 0
        substate_general = 0
        tool_count = 10000
        substate_tool = 10000
        toolName = ''

        # we used this as True for creating the software
        debug_substate_tool_found = False

        if ( reset ):
            self.resetDspFile()

        c_None               = 0
        c_FilterGroupSection = 1
        c_FileSection        = 2
        c_FileConfigSection  = 3
        c_ToolSection        = 4

        keyToContinue = True
        entryNameMultiline = ''
        entryValueMultiline = ''
        entryValueMultilineNumLines = 0

        vcpHdr = VcprojGeneralSectionData()
        vcpFiles = VcprojFilesSectionData()

        toolName = ''

        #groupname = ''
        c_InitialLevel = 0
        level = c_InitialLevel
        fgIdx = -1
        previousFilterGroup = None

        isKey = 0 # 1 --> Filter ; 2 --> File; 3 --> FileConfiguration; 4 --> Tool
        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n + 1
            #if ( 157 <= self.n ): # %%%
            #    ndbg = 0

            # skips the configurations body but save it into sectionBeforeLines
            if ( state == 0 ):
                keyFound = False

                #<?xml version="1.0" encoding = "Windows-1252"?>
                m_vcp_general_version_xml = re_vcp_general_version_xml.match( line )
                if ( m_vcp_general_version_xml ):
                    vcpHdr.version_xml = m_vcp_general_version_xml.group( 'version_xml' )
                    vcpHdr.encoding_xml = m_vcp_general_version_xml.group( 'encoding_xml' )
                    expectedXmlVersion = '1.0'
                    if ( vcpHdr.version_xml != expectedXmlVersion ):
                        print 'WARNING: xml version of the vcproj [%s] is not expected [%s]. File \'%s\'(%d). Line \'%s\'' % ( vcpHdr.version_xml, expectedXmlVersion, self.filetitle, self.n, line.rstrip() )
                    substate_general = substate_general + 1
                    keyFound = True
                    continue

                #<VisualStudioProject
                m_vcp_general_visualStudioProject_beg = re_vcp_general_visualStudioProject_beg.match( line )
                if ( m_vcp_general_visualStudioProject_beg ):
                    substate_general = substate_general + 1
                    keyFound = True
                    continue

                #       <Platforms>
                m_vcp_general_platforms_beg = re_vcp_general_platforms_beg.match( line )
                if ( m_vcp_general_platforms_beg ):
                    substateExpected = 5
                    if ( debug_substate_tool_found and substate_general != substateExpected ):
                        raise Exception( 'getEntriesVcproj: We found only %d of %d entries expected in the general section. File \'%s\'(%d). Line \'%s\'' % ( substate_general, substateExpected, self.filetitle, self.n, line.rstrip() ) )
                    state = 1
                    substate_general = 10000
                    tool_count = 10000
                    substate_tool = 10000
                    keyFound = True
                    continue

                m_vcp_entry = re_vcp_entry.match( line )
                if ( m_vcp_entry ):
                    entryName = m_vcp_entry.group( 'entryName' )
                    entryValue = m_vcp_entry.group( 'entryValue' )
                    vcpHdr.entryNamesList.append( entryName )
                    vcpHdr.entryNameValueDict[ entryName ] = entryValue
                    if ( entryName == 'Version' ):
                        vcpHdr.version_vc_project = entryValue
                        if ( compiler == compilerVc70 ):
                            if ( not vcpHdr.version_vc_project == '7.00' ):
                                raise Exception( 'Version of the vcproj [%s] is incompatible with the expected compiler [%s]. File \'%s\'(%d). Line \'%s\'' % ( vcpHdr.version_vc_project, compiler, self.filetitle, self.n, line.rstrip() ) )
                        if ( compiler == compilerVc71 ):
                            if ( not vcpHdr.version_vc_project == '7.10' ):
                                raise Exception( 'Version of the vcproj [%s] is incompatible with the expected compiler [%s]. File \'%s\'(%d). Line \'%s\'' % ( vcpHdr.version_vc_project, compiler, self.filetitle, self.n, line.rstrip() ) )
                    elif ( entryName == 'Name' ):
                        vcpHdr.trueProjectName = entryValue
                    else:
                        pass

                    #raise Exception( 'please add the key \'%s\' to the struct VcprojGeneralSectionData and create a specific regular expression for the key. ( %s=\"%s\" ).  File \'%s\' (%d). Line \'%s\'' % ( entryName, entryName, entryValue, self.filetitle, self.n, line.rstrip() ) )
                    substate_general = substate_general + 1
                    keyFound = True
                    continue

                if ( False ):
                    # this must be the last !
                    m_vcp_entry_cont0 = re_vcp_entry_cont0.match( line )
                    if ( m_vcp_entry_cont0 ):
                        entryNameMultiline = m_vcp_entry_cont0.group( 'entryName' )
                        value = m_vcp_entry_cont0.group( 'entryValueMultiline' )
                        keyToContinue = True
                        entryValueMultilineNumLines = 0
                        entryValueMultiline = value + '\n'
                        substate_general = substate_general + 1
                        keyFound = True
                        continue

                    if ( keyToContinue ):
                        m_vcp_entry_cont1 = re_vcp_entry_cont1.match( line )
                        if ( m_vcp_entry_cont1 ):
                            value = m_vcp_entry_cont1.group( 'entryValueMultiline' )
                            keyToContinue = True
                            value = value.rstrip()
                            entryValueMultilineNumLines = entryValueMultilineNumLines + 1
                            entryValueMultiline = entryValueMultiline + value + '\n'
                            if ( value[-1] == '\"' ):
                                entryName = entryNameMultiline
                                if ( not entryName == entryNameMultiline ):
                                    raise Exception( 'getEntriesVcproj: it should be (entryName == entryNameMultiline). Instead is (%s != %s)' % ( entryName, entryNameMultiline ) )
                                entryValue = value
                                vcpTool.entryNamesList.append( entryName )
                                vcpTool.entryNameValueDict[ entryName ] = entryValueMultiline
                                entryNameMultiline = ''
                                keyToContinue = False
                            substate_general = substate_general + 1
                            keyFound = True
                            continue

                if ( not keyFound ):
                    raise Exception( 'getEntriesVcproj: bad parsing, key not found. File \'%s\' (%d). Line \'%s\'' % ( self.filetitle, self.n, line.rstrip() ) )

            elif ( state == 1 ):
                keyFound = False

                #               <Platform
                m_vcp_general_platform_beg = re_vcp_general_platform_beg.match( line )
                if ( m_vcp_general_platform_beg ):
                    substate_general = 0
                    tool_count = 10000
                    substate_tool = 10000
                    keyFound = True
                    continue

                #                       Name="Win32"/>
                m_vcp_keyname = re_vcp_keyname.match( line )
                if ( m_vcp_keyname ):
                    keyname = m_vcp_keyname.group( 'keyname' )
                    vcpHdr.platformName = keyname
                    if ( vcpHdr.platformName != 'Win32' ):
                        raise Exception( 'getEntriesVcproj: Unexpected platform: %s ( the expected one is \'%s\ )\'. File \'%s\'(%d). Line \'%s\'' % ( vcpHdr.platformName, 'Win32', self.filetitle, self.n, line.rstrip() ) )
                    substate_general = substate_general + 1
                    keyFound = True
                    continue

                #       </Platforms>
                m_vcp_general_platforms_end = re_vcp_general_platforms_end.match( line )
                if ( m_vcp_general_platforms_end ):
                    substateExpected = 1
                    if ( debug_substate_tool_found and substate_general != substateExpected ):
                        raise Exception( 'getEntriesVcproj: We found only %d of %d entries expected in the general section. File \'%s\'(%d). Line \'%s\'' % ( substate_tool, substateExpected, self.filetitle, self.n, line.rstrip() ) )
                    state = 2
                    substate_general = 10000
                    tool_count = 10000
                    substate_tool = 10000
                    keyFound = True
                    continue

                if ( not keyFound ):
                    raise Exception( 'getEntriesVcproj: bad parsing, key not found. File \'%s\' (%d). Line \'%s\'' % ( self.filetitle, self.n, line.rstrip() ) )

            elif ( state == 2 ):
                keyFound = False

                #       <Configurations>
                m_vcp_config_configurations_beg = re_vcp_config_configurations_beg.match( line )
                if ( m_vcp_config_configurations_beg ):
                    substate_tool = 0
                    tool_count = 0
                    tool_count_expected = 0
                    keyFound = True
                    continue

                #               <Configuration
                m_vcp_config_configuration_beg = re_vcp_config_configuration_beg.match( line )
                if ( m_vcp_config_configuration_beg ):
                    substate_tool = 0
                    tool_count = 0 # number of <Tool$ sections plus the config's header
                    toolName = '' # '_configuration_header_' # we expect only one platform
                    expectedToolName = '' # '_configuration_header_'
                    if ( compiler == compilerVc70 ):
                        tool_count_expected = 10
                    elif ( compiler == compilerVc71 ):
                        tool_count_expected = 13
                    substate_tool_expected = 7

                    # new struct
                    vcpCfg = VcprojConfigSectionData()

                    # new tool data
                    #vcpTool = VcprojToolSectionData()
                    #vcpTool.tool_name = '_configuration_header_'

                    # flag for no <Tool met yet
                    toolName = ''
                    keyFound = True
                    continue


                #               </Configuration>
                m_vcp_config_configuration_end = re_vcp_config_configuration_end.match( line )
                if ( m_vcp_config_configuration_end ):
                    #if ( tool_count != tool_count_expected ):
                    #    raise Exception( 'getEntriesVcproj: We found only %d of %d entries expected in this config section [%s]. File \'%s\'(%d). Line \'%s\'' % ( tool_count, tool_count_expected, vcpCfg.config_name, self.filetitle, self.n, line.rstrip() ) )
                    if ( debug_substate_tool_found and substate_tool != substate_tool_expected ):
                        raise Exception( 'getEntriesVcproj: We found only %d of %d entries expected in this tool section [%s]. Configuration [%s]. File \'%s\'(%d). Line \'%s\'' % ( substate_tool, substate_tool_expected, toolName, vcpCfg.config_name, self.filetitle, self.n, line.rstrip() ) )

                    # store the data for the last tool just completed
                    vcpCfg.toolNamesList.append( vcpTool.tool_name )
                    vcpCfg.toolNameSectionsDict[ vcpTool.tool_name ] = vcpTool

                    # store the data for the config just completed

                    configFullName = vcpCfg.config_name
                    configFullNameLwr = configFullName.lower()
                    vcpHdr.configurationFullNamesList.append( configFullName )
                    vcpHdr.configurationsFullNameSectionsDict[ configFullNameLwr ] = vcpCfg

                    substate_tool = 10000
                    tool_count = 0 # number of <Tool$ sections plus the config's header
                    toolName = '' # we expect only one platform
                    expectedToolName = ''
                    tool_count_expected = 0
                    keyFound = True
                    continue

                #       </Configurations>
                m_vcp_config_configurations_end = re_vcp_config_configurations_end.match( line )
                if ( m_vcp_config_configurations_end ):
                    tool_count_expected = 10000
                    substate_tool_expected = 10000
                    state = 3
                    keyFound = True
                    continue


                #                       <Tool
                m_vcp_sectionTool_beg = re_vcp_sectionTool_beg.match( line )
                if ( m_vcp_sectionTool_beg ):
                    if ( debug_substate_tool_found and substate_tool != substate_tool_expected ):
                        raise Exception( 'getEntriesVcproj: We found only %d of %d entries expected in this tool section [%s]. Configuration [%s]. File \'%s\'(%d). Line \'%s\'' % ( substate_tool, substate_tool_expected, toolName, vcpCfg.config_name, self.filetitle, self.n, line.rstrip() ) )

                    if ( False ):
                        if ( toolName ):
                            #if ( toolName == '_configuration_header_' ):
                            #    expectedToolName = 'VCCLCompilerTool'
                            #    substate_tool_expected = 15
                            #
                            #
                            #elif ( toolName == 'VCAuxiliaryManagedWrapperGeneratorTool' ):
                            #    expectedToolName = ''
                            #    substate_tool_expected = 1
                            #else:
                            #    raise Exception( 'getEntriesVcproj: Unexpected toolName [%s]. Configuration [%s]. File \'%s\'(%d). Line \'%s\'' % ( toolName, vcpCfg.config_name, self.filetitle, self.n, line.rstrip() ) )
                            pass
                        else:
                            raise Exception( 'getEntriesVcproj: Unexpected empty toolName [%s]. Configuration [%s]. File \'%s\'(%d). Line \'%s\'' % ( toolName, vcpCfg.config_name, self.filetitle, self.n, line.rstrip() ) )

                    # store the data for the tool just completed
                    if ( toolName != '' ):
                        vcpCfg.toolNamesList.append( vcpTool.tool_name )
                        vcpCfg.toolNameSectionsDict[ vcpTool.tool_name ] = vcpTool

                    # new tool data
                    vcpTool = VcprojToolSectionData()

                    tool_count = tool_count + 1
                    substate_tool = 0

                    # flag for no <Tool ... Name met yet
                    toolName = ''
                    keyFound = True
                    continue


                #                       Name="Debug|Win32"
                m_vcp_keyname = re_vcp_keyname.match( line )
                if ( m_vcp_keyname ):
                    keyname = m_vcp_keyname.group( 'keyname' )
                    #if ( expectedToolName != keyname ):
                    #    if ( expectedToolName != '_configuration_header_' ):
                    #        raise Exception( 'getEntriesVcproj: Unexpected tool name: %s ( the expected is \'%s\' ). Configuration [%s]. File \'%s\'(%d). Line \'%s\'' % ( keyname, expectedToolName, vcpCfg.config_name, self.filetitle, self.n, line.rstrip() ) )
                    #if ( expectedToolName != '_configuration_header_' ):
                    #    toolName = keyname
                    #if ( expectedToolName == '_configuration_header_' ):
                    #    vcpCfg.config_name = keyname
                    #elif ( expectedToolName == 'VCCLCompilerTool' ):
                    #    vcpCfg.nameTool_VCCLCompilerTool = keyname
                    #
                    #
                    #else:
                    #    raise Exception( 'getEntriesVcproj: Unexpected toolName [%s]. Configuration [%s]. File \'%s\'(%d). Line \'%s\'' % ( toolName, vcpCfg.config_name, self.filetitle, self.n, line.rstrip() ) )

                    if ( vcpCfg.config_name == '' ):
                        vcpCfg.config_name = keyname
                        entryName = 'Name'
                        entryValue = keyname
                        vcpCfg.entryNamesList.append( entryName )
                        vcpCfg.entryNameValueDict[ entryName ] = entryValue
                    else:
                        vcpTool.tool_name = keyname
                        entryName = 'Name'
                        entryValue = keyname
                        vcpTool.entryNamesList.append( entryName )
                        vcpTool.entryNameValueDict[ entryName ] = entryValue
                        toolName = keyname

                    substate_tool = substate_tool + 1
                    keyFound = True
                    continue


                #               AdditionalIncludeDirectories="$(VCF_INCLUDE)"
                #                               ProgramDataBaseFileName=".\vc70/Debug/"
                #                               WarningLevel="3"
                m_vcp_entry = re_vcp_entry.match( line )
                if ( m_vcp_entry ):
                    entryName = m_vcp_entry.group( 'entryName' )
                    entryValue = m_vcp_entry.group( 'entryValue' )
                    if ( toolName == '' ):
                        vcpCfg.entryNamesList.append( entryName )
                        vcpCfg.entryNameValueDict[ entryName ] = entryValue
                    else:
                        vcpTool.entryNamesList.append( entryName )
                        vcpTool.entryNameValueDict[ entryName ] = entryValue
                    substate_tool = substate_tool + 1
                    keyFound = True
                    continue

                # this must be the last: it is for keys that are multilines
                # the regular expression to match them matches almost everything
                m_vcp_entry_cont0 = re_vcp_entry_cont0.match( line )
                if ( m_vcp_entry_cont0 ):
                    entryNameMultiline = m_vcp_entry_cont0.group( 'entryName' )
                    value = m_vcp_entry_cont0.group( 'entryValueMultiline' )
                    keyToContinue = True
                    entryValueMultilineNumLines = 0
                    entryValueMultiline = value + '\n'
                    #substate_general = substate_general + 1
                    keyFound = True
                    continue

                # this is the continuation of a multiline key
                if ( keyToContinue ):
                    m_vcp_entry_cont1 = re_vcp_entry_cont1.match( line )
                    if ( m_vcp_entry_cont1 ):
                        value = m_vcp_entry_cont1.group( 'entryValueMultiline' )
                        keyToContinue = True
                        value = value.rstrip()
                        entryValueMultilineNumLines = entryValueMultilineNumLines + 1
                        if ( value[-1] == '\"' ):
                            # eliminates last '\"' and also no '\n' at the end
                            entryValueMultiline = entryValueMultiline + value[:-1]
                            entryName = entryNameMultiline
                            if ( not entryName == entryNameMultiline ):
                                raise Exception( 'getEntriesVcproj: it should be (entryName == entryNameMultiline). Instead is (%s != %s)' % ( entryName, entryNameMultiline ) )
                            entryValue = value
                            vcpTool.entryNamesList.append( entryName )
                            vcpTool.entryNameValueDict[ entryName ] = entryValueMultiline
                            entryNameMultiline = ''
                            keyToContinue = False
                        else:
                            # store another line
                            entryValueMultiline = entryValueMultiline + value + '\n'

                        #substate_general = substate_general + 1
                        substate_tool = substate_tool + 1
                        keyFound = True
                        continue


                if ( not keyFound ):
                    raise Exception( 'getEntriesVcproj: bad parsing, key not found. File \'%s\' (%d). Line \'%s\'' % ( self.filetitle, self.n, line.rstrip() ) )

            #   <Files>
            elif ( state == 3 ):
                if ( re_vcp_sectionFiles_beg.match( line ) ):
                    #vcpFiles = VcprojFilesSectionData()
                    state =4
                    continue
                self.sectionBeforeLines.append( line )

            elif ( state == 4 ):
                keyFound = False

                #               <Filter>
                m_vcp_sectionFilter_beg = re_vcp_sectionFilter_beg.match( line )
                if ( m_vcp_sectionFilter_beg ):
                    # to increment the level here or at the end of this function is pretty much the same thing
                    level = level + 1

                    if ( 0 <= fgIdx ):
                        previousFilterGroup = vcpFiltergrp

                    # new FilterGroup data
                    vcpFiltergrp = VcprojFilterGroupSectionData()
                    #vcpFiltergrp.name = groupname
                    vcpFiltergrp.level = level

                    if ( c_InitialLevel + 1 == level ):
                        vcpFiles.attachChild( vcpFiltergrp )
                    else:
                        if ( previousFilterGroup.level < level ):
                            vcpFiltergrp.attachAsChildOf( previousFilterGroup )
                        else:
                            vcpFiltergrp.attachAsSiblingOf( previousFilterGroup )

                    # store it immediately: it is a queue. So the order is preserved!
                    vcpFiles.filtergroupNamesList.append( vcpFiltergrp.name )
                    fgIdx = fgIdx + 1
                    vcpFiles.filtergroupNameValueDict[ vcpFiltergrp.name.lower() ] = vcpFiltergrp

                    if ( g_printFilterGroupTrees and self.isFileIn2() ):
                        print 'getSouceEntriesDsp: file: %s' % self.filetitle
                        vcpFiles.printChildren( '.', 'vcpFiles' )

                    # store it immediately: it is a queue. So the order is preserved!
                    # well.. we store it when we have its name !
                    #vcpFiles.filtergroupNamesList.append( vcpFiltergrp.name )
                    #fgIdx = fgIdx + 1
                    #vcpFiles.filtergroupNameValueDict[ vcpFiltergrp.name.lower() ] = vcpFiltergrp

                    isKey = c_FilterGroupSection # 1
                    keyFound = True
                    continue

                #               <File
                m_vcp_sectionFile_beg = re_vcp_sectionFile_beg.match( line )
                if ( m_vcp_sectionFile_beg ):
                    # new File data
                    vcpFile = VcprojFileSectionData()

                    isKey = c_FileSection # 2
                    keyFound = True
                    continue

                #           <FileConfiguration
                m_vcp_sectionFileConfig_beg = re_vcp_sectionFileConfig_beg.match( line )
                if ( m_vcp_sectionFileConfig_beg ):
                    # commented because we have a </FileConfiguration>
                    # store the data for the FileConfiguration just completed
                    #vcpFile.fileConfigNamesList.append( vcpFilecfg.fileConfig_name )
                    #vcpFile.fileConfigNameSectionsDict[ vcpFilecfg.fileConfig_name ] = vcpFilecfg

                    # new FileConfiguration data
                    vcpFilecfg = VcprojFileConfigurationSectionData()

                    toolName = ''

                    isKey = c_FileConfigSection # 3
                    keyFound = True
                    continue

                #                <Tool
                m_vcp_sectionTool_beg = re_vcp_sectionTool_beg.match( line )
                if ( m_vcp_sectionTool_beg ):
                    # store the data for the last tool completed if existing one
                    if ( toolName ):
                        vcpFilecfg.toolNamesList.append( vcpTool.tool_name )
                        vcpFilecfg.toolNameSectionsDict[ vcpTool.tool_name ] = vcpTool

                    # new tool data
                    vcpTool = VcprojToolSectionData()

                    isKey = c_ToolSection # 4
                    keyFound = True
                    continue

                #                <FileConfiguration
                m_vcp_sectionFileConfig_end = re_vcp_sectionFileConfig_end.match( line )
                if ( m_vcp_sectionFileConfig_end ):
                    # store the data for the last tool completed
                    if ( toolName ):
                        vcpFilecfg.toolNamesList.append( vcpTool.tool_name )
                        vcpFilecfg.toolNameSectionsDict[ vcpTool.tool_name ] = vcpTool

                    # store the data for the last FileConfiguration just completed
                    vcpFile.fileConfigNamesList.append( vcpFilecfg.fileConfig_name )
                    fileConfig_nameLwr = vcpFilecfg.fileConfig_name.lower()
                    vcpFile.fileConfigNameSectionsDict[ fileConfig_nameLwr ] = vcpFilecfg

                    isKey = c_None # 0
                    keyFound = True
                    continue # this continue is particularly important

                #               </File>
                m_vcp_sectionFile_end = re_vcp_sectionFile_end.match( line )
                if ( m_vcp_sectionFile_end ):
                    #fg = vcpFiles.filtergroupNameValueDict[ vcpFiles.filtergroupNamesList[ fgIdx ].lower() ]
                    #fg.fileNamesList.append( vcpFile.file_name ) # we know that they are unique

                    if ( 0 == level ):
                        container = vcpFiles
                    else:
                        container = vcpFiltergrp

                    container.fileNamesList.append( vcpFile.file_name ) # we know that they are unique
                    filenameLwr = vcpFile.file_name.lower()
                    if ( container.fileNameFileDict.has_key( filenameLwr ) ):
                        raise Exception( 'The file \'%s\' already exists in this FilterGroup section [%s]. File \'%s\' (%d). Line \'%s\'' % ( vcpFile.file_name, container.name, self.filetitle, self.n, line.rstrip() ) )
                    container.fileNameFileDict[ filenameLwr ] = vcpFile

                    isKey = c_None # 0
                    keyFound = True
                    continue

                #               </Filter>
                m_vcp_sectionFilter_end = re_vcp_sectionFilter_end.match( line )
                if ( m_vcp_sectionFilter_end ):
                    # at the beginning because += 1 is done at the end of the <Filter management
                    level = level - 1

                    # for the other <file>s still to attach or whatever sub filter we have
                    # the 'current group is now the parent one !
                    vcpFiltergrp = vcpFiltergrp.parent


                    isKey = c_None # 0
                    keyFound = True
                    continue

                #               Name="Release|Win32"
                #                       Name="Source Files"
                m_vcp_keyname = re_vcp_keyname.match( line )
                if ( m_vcp_keyname ):
                    keyname = m_vcp_keyname.group( 'keyname' )
                    if ( isKey == c_FilterGroupSection ):

                        # we store as soon as we have the name: it is a queue. So the order is preserved!
                        vcpFiltergrp.name = keyname
                        vcpFiles.filtergroupNamesList.append( vcpFiltergrp.name )
                        fgIdx = fgIdx + 1
                        vcpFiles.filtergroupNameValueDict[ vcpFiltergrp.name.lower() ] = vcpFiltergrp

                        ##groupname = m_vcp_group.group( 'groupname' )
                        #groupname = dspFiltergrpData.groupname # with dsp is called group, with vcproj is called filter
                        #dspFiltergrpData.groupname = groupname
                    elif( isKey == c_FileSection ):
                        pass
                    elif( isKey == c_FileConfigSection ):
                        vcpFilecfg.fileConfig_name = keyname
                        confignamePlatform = vcpFilecfg.fileConfig_name
                        confignamePlatformLwr = confignamePlatform.lower()

                        #vcpFile.fileConfigNameSectionsDict[ vcpFilecfg.fileConfig_name ] = vcpFilecfg

                        if ( StringUtils.findInList( confignamePlatformLwr, self.listGroupNamesConfigOrPlatformLwr ) == -1 ):
                            ( config, platform ) = confignamePlatform.split( '|' )
                            configOrPlatform = '%s|%s' % ( config, platform )
                            if ( configOrPlatform != confignamePlatform ):
                                raise Exception( 'bad parsing of <config|platform>: (%s!=%s). Read %d lines in \'%s\'. Line \'%s\'' % ( confignamePlatform, configOrPlatform, self.n, self.filetitle, line.rstrip() ) )
                            self.listGroupNamesConfigOrPlatform.append( configOrPlatform )
                            self.listGroupNamesConfigOrPlatformLwr.append( configOrPlatform.lower() )
                            self.listGroupNamesConfig.append( config )
                            self.listGroupNamesPlatform.append( platform )
                    elif( isKey == c_ToolSection ):
                        vcpTool.tool_name = keyname
                        toolName = keyname
                        entryName = 'Name'
                        entryValue = keyname
                        vcpTool.entryNamesList.append( entryName )
                        vcpTool.entryNameValueDict[ entryName ] = entryValue
                        #self.dictTools[ basenameLwr ] = vcpTool.tool_name
                    keyFound = True
                    continue

                #                       Filter="cpp;c;cxx;rc;def;r;odl;idl;hpj;bat">
                m_vcp_sectionFilter_content = re_vcp_sectionFilter_content.match( line )
                if ( m_vcp_sectionFilter_content ):
                    #fg = vcpFiles.filtergroupNameValueDict[ vcpFiles.filtergroupNamesList[ fgIdx ].lower() ]
                    #fg.value = m_vcp_sectionFilter_content.group( 'filtervalue' )
                    vcpFiltergrp.value = m_vcp_sectionFilter_content.group( 'filtervalue' )
                    keyFound = True
                    continue

                #                               RelativePath="..\FreeImage\PluginBMP.cpp">
                m_vcp_sectionFile_content = re_vcp_sectionFile_content.match( line )
                if ( m_vcp_sectionFile_content ):
                    source = m_vcp_sectionFile_content.group( 'sourcename' )
                    source = FileUtils.normPath( source, g_internal_unixStyle )
                    #dspFiltergrpData.listSourceNames.append( source )

                    basename = os.path.basename( source )
                    basenameLwr = basename.lower()
                    #dspFiltergrpData.dictSourceNames[ basenameLwr ] = source
                    self.dictSourceNames[ basenameLwr ] = source

                    vcpFile.file_relativepath = source
                    vcpFile.file_name = basename
                    keyFound = True
                    continue

                #                                               Optimization="0"
                #                                               AdditionalIncludeDirectories=""
                #                                               PreprocessorDefinitions=""
                #                                               BasicRuntimeChecks="3"
                m_vcp_entry = re_vcp_entry.match( line )
                if ( m_vcp_entry ):
                    entryName = m_vcp_entry.group( 'entryName' )
                    entryValue = m_vcp_entry.group( 'entryValue' )
                    vcpTool.entryNamesList.append( entryName )
                    vcpTool.entryNameValueDict[ entryName ] = entryValue
                    keyFound = True
                    continue

                #       </Files>
                m_vcp_sectionFiles_end = re_vcp_sectionFiles_end.match( line )
                if ( m_vcp_sectionFiles_end ):
                    state = 5
                    keyFound = True
                    continue

                # this must be the last: it is for keys that are multilines
                # the regular expression to match them matches almost everything
                m_vcp_entry_cont0 = re_vcp_entry_cont0.match( line )
                if ( m_vcp_entry_cont0 ):
                    entryNameMultiline = m_vcp_entry_cont0.group( 'entryName' )
                    value = m_vcp_entry_cont0.group( 'entryValueMultiline' )
                    keyToContinue = True
                    entryValueMultilineNumLines = 0
                    entryValueMultiline = value + '\n'
                    substate_general = substate_general + 1
                    keyFound = True
                    continue

                # this is the continuation of a multiline key
                if ( keyToContinue ):
                    m_vcp_entry_cont1 = re_vcp_entry_cont1.match( line )
                    if ( m_vcp_entry_cont1 ):
                        value = m_vcp_entry_cont1.group( 'entryValueMultiline' )
                        keyToContinue = True
                        value = value.rstrip()
                        entryValueMultilineNumLines = entryValueMultilineNumLines + 1
                        if ( value[-1] == '\"' ):
                            # eliminates last '\"' and also no '\n' at the end
                            entryValueMultiline = entryValueMultiline + value[:-1]
                            entryName = entryNameMultiline
                            if ( not entryName == entryNameMultiline ):
                                raise Exception( 'getEntriesVcproj: it should be (entryName == entryNameMultiline). Instead is (%s != %s)' % ( entryName, entryNameMultiline ) )
                            entryValue = value
                            vcpTool.entryNamesList.append( entryName )
                            vcpTool.entryNameValueDict[ entryName ] = entryValueMultiline
                            entryNameMultiline = ''
                            keyToContinue = False
                        else:
                            # store another line
                            entryValueMultiline = entryValueMultiline + value + '\n'

                        substate_general = substate_general + 1
                        keyFound = True
                        continue

                if ( not keyFound ):
                    raise Exception( 'getEntriesVcproj: bad parsing, key not found. File \'%s\' (%d). Line: \'%s\'' % ( self.filetitle, self.n, line.rstrip() ) )

            elif ( state == 5 ):
                self.sectionAfterLines.append( line )

                if ( 0 != level ):
                    msg = 'getEntriesVcproj: ***ERROR*** completed but the level is not null [%d]. File \'%s\' ' % ( level, self.filename )
                    print( msg )
                    #raise Exception( msg )

                state = 6


        if ( state != 6 ):
            raise Exception( 'getEntriesVcproj: wrong final state: [%d]. Read %d lines in \'%s\'' % ( state, self.n, self.filetitle ) )

        #raise Exception( 'Not implemented yet' )
        #dspSrc = DspSourceData()

        return ( vcpHdr, vcpFiles )

    def convertEntriesVcproj( self, vcpHdrSrc, vcpFilesSrc, oldCompiler, newCompiler, convertProjectConfigSection = True ):
        # Note part of the conversion work is already done by writelineEntriesVcprojAsStruct
        # because it does not write what is not accepted by that compiler's version

        # Here we need to add few entries if necessary

        # we need of vcpHdrSrc to convert the files because we need of the list of configurations
        # but for no other reasons. So please specify convertProjectConfigSection = False
        # if you don't want to convert the vcpHdr

        if ( not vcpHdrSrc ):
            raise Exception( 'convertEntriesVcproj: vcpHdrSrc is necessary for any conversion' )

        oldCompilerVersion = g_mapCompilerNameVersion[ oldCompiler ]
        newCompilerVersion = g_mapCompilerNameVersion[ newCompiler ]

        vcpHdr = VcprojGeneralSectionData()
        vcpHdr.copy( vcpHdrSrc )

        replaceCompilerTuple = DspFile.replaceCompilerTextMakeTuple( oldCompiler, newCompiler )

        if ( convertProjectConfigSection ):
            #<Configurations ...> ... </Configurations> section

            if ( newCompiler == compilerVc6 ):
                vcpHdr.version_vc_project = '6.00'
            elif ( newCompiler == compilerVc70 ):
                vcpHdr.version_vc_project = '7.00'
            else: # ( newCompiler == compilerVc71 ):
                vcpHdr.version_vc_project = '7.10'
            vcpHdr.entryNameValueDict[ 'Version' ] = vcpHdr.version_vc_project

            for config_name in vcpHdr.configurationFullNamesList:
                config_nameLwr = config_name.lower()
                vcpCfg = vcpHdr.configurationsFullNameSectionsDict[ config_nameLwr ]

                # first gets the ConfigurationType
                isDebug = ( config_nameLwr.find( 'debug' ) != -1 )
                appType = enumAppTypeNone
                for entryName in vcpCfg.entryNamesList:
                    entryValue = vcpCfg.entryNameValueDict[ entryName ]
                    if ( entryName == 'ConfigurationType' ):
                        appType = DspFile.translateConfigurationType( eval( entryValue ) )
                        break

                # reformats/converts all the path entries
                for entryName in vcpCfg.entryNamesList:
                    entryValue = vcpCfg.entryNameValueDict[ entryName ]
                    changed = False
                    if ( entryValue and g_mapPathEntries.has_key( entryName ) ):
                        entryValue = FileUtils.normPath( entryValue, app.options.unixStyle, g_keepFirstDot_standard, g_MinPathIsDot_True, g_IsDirForSure_ChkDot )
                        entryValue = self.fixFilenamePostfix( entryValue, oldCompiler, newCompiler, appType, isDebug, config_name )
                        entryValue = DspFile.replaceCompilerTextTuple( entryValue, replaceCompilerTuple )
                        changed = True
                    if ( entryName == 'AdditionalDependencies' ):
                        entryValue = self.librariesChangePostfix( entryValue, oldCompiler, newCompiler, appType, isDebug, config_name )
                        changed = True
                    if ( entryName == 'ImportLibrary' ):
                        entryValue = DspFile.replaceCompilerTextTuple( entryValue, replaceCompilerTuple )
                        changed = True
                    # make sure the newCompiler postfix is there instead than the oldCompiler one ( this fixes ImportLibrary= too )
                    entryValue = DspFile.replaceCompilersText( entryValue, newCompiler )
                    changed = True
                    if ( changed ):
                        vcpCfg.entryNameValueDict[ entryName ] = entryValue

                for tool_name in vcpCfg.toolNamesList:
                    vcpTool = vcpCfg.toolNameSectionsDict[ tool_name ]
                    for entryName in vcpTool.entryNamesList:
                        entryValue = vcpTool.entryNameValueDict[ entryName ]
                        changed = False
                        if ( entryValue and g_mapPathEntries.has_key( entryName ) ):
                            entryValue = FileUtils.normPath( entryValue, app.options.unixStyle, g_keepFirstDot_standard, g_MinPathIsDot_True, g_IsDirForSure_ChkDot )
                            entryValue = self.fixFilenamePostfix( entryValue, oldCompiler, newCompiler, appType, isDebug, config_name )
                            entryValue = DspFile.replaceCompilerTextTuple( entryValue, replaceCompilerTuple )
                            changed = True
                        if ( entryName == 'AdditionalDependencies' ):
                            entryValue = self.librariesChangePostfix( entryValue, oldCompiler, newCompiler, appType, isDebug, config_name )
                            changed = True
                        # make sure the newCompiler postfix is there instead than the oldCompiler one ( this fixes ImportLibrary= too )
                        entryValue = DspFile.replaceCompilersText( entryValue, newCompiler )
                        changed = True
                        if ( changed ):
                            vcpTool.entryNameValueDict[ entryName ] = entryValue

                # add tools and entries existing only on ( compilerVc71 <= compilers )
                if ( addToolsForVc71WhenSynchToVc70 ):
                    if ( compilerVc71 <= newCompiler ):
                        for tn in g_vecToolNamesVc71:
                            if ( g_mapToolsOnlyVc71.has_key( tn  ) ):
                                # add tools if not there yet
                                if ( not vcpCfg.toolNameSectionsDict.has_key( tn ) ):
                                    vcpTool = VcprojToolSectionData()
                                    vcpTool.compiler_version = compilerVersionVc71
                                    vcpTool.tool_name = tn
                                    vcpTool.entryNamesList.append( 'Name' )
                                    vcpTool.entryNameValueDict[ 'Name' ] = vcpTool.tool_name
                                    vcpCfg.toolNamesList.append( vcpTool.tool_name )
                                    vcpCfg.toolNameSectionsDict[ vcpTool.tool_name ] = vcpTool

                            # add entries if not there yet
                            for k, v in g_mapToolEntriesOnlyVc71.iteritems():
                                if ( vcpCfg.toolNameSectionsDict.has_key( v ) ):
                                    vcpTool = vcpCfg.toolNameSectionsDict[ v ]
                                    if ( not vcpTool.entryNameValueDict.has_key( k ) ):
                                        #vcpTool.entryNamesList.append( k )
                                        #vcpTool.entryNameValueDict[ k ] = g_mapToolEntriesOnlyVc71DefaultValues[ k ]
                                        vcpTool.appendEntryKeyValue( k, g_mapToolEntriesOnlyVc71DefaultValues[ k ] )


        # <Files ...> ... </Files> section
        vcpFiles = None
        if ( vcpFilesSrc ):
            vcpFiles = VcprojFilesSectionData()
            vcpFiles.copy( vcpFilesSrc )

            if ( addEntriesForVc71WhenSynchToVc70 ):
                for name in vcpFiles.filtergroupNamesList:
                    filtergroup_nameLwr = name.lower()
                    vcpFiltergrp = vcpFiles.filtergroupNameValueDict[ filtergroup_nameLwr ]
                    for file_name in vcpFiltergrp.fileNamesList:
                        file_nameLwr = file_name.lower()
                        ( root, ext ) = os.path.splitext( file_nameLwr )
                        if ( ext == '.cpp' ):
                            vcpFile = vcpFiltergrp.fileNameFileDict[ file_nameLwr ]
                            # we need to add all the fileConfigurations !
                            for config_name in vcpHdr.configurationFullNamesList:
                                config_nameLwr = config_name.lower()
                                if ( vcpFile.fileConfigNameSectionsDict.has_key( config_nameLwr ) ):
                                    vcpFilecfg = vcpFile.fileConfigNameSectionsDict[ config_nameLwr ]
                                else:
                                    vcpFilecfg = VcprojFileConfigurationSectionData()
                                    vcpFilecfg.fileConfig_name = config_name
                                    vcpFile.fileConfigNameSectionsDict[ config_nameLwr ] = vcpFilecfg
                                # and we add the 'VCCLCompilerTool'
                                vcpTool = VcprojToolSectionData()
                                vcpTool.tool_name = 'VCCLCompilerTool'
                                vcpTool.entryNamesList.append( 'Name' )
                                vcpTool.entryNameValueDict[ 'Name' ] = vcpTool.tool_name
                                vcpFilecfg.toolNamesList.append( vcpTool.tool_name )            # we can do it before too
                                vcpFilecfg.toolNameSectionsDict[ vcpTool.tool_name ] = vcpTool  # we can do it before too
                                if ( vcpFilecfg.fileConfig_name.lower().find( 'debug' ) != -1 ):
                                    vcpTool.appendEntryKeyValue( 'Optimization',                   '0' )
                                    vcpTool.appendEntryKeyValue( 'AdditionalIncludeDirectories',   ''  )
                                    vcpTool.appendEntryKeyValue( 'PreprocessorDefinitions',        ''  )
                                    vcpTool.appendEntryKeyValue( 'BasicRuntimeChecks',             '3' )
                                else:
                                    vcpTool.appendEntryKeyValue( 'Optimization',                   '1' )
                                    vcpTool.appendEntryKeyValue( 'AdditionalIncludeDirectories',   ''  )
                                    vcpTool.appendEntryKeyValue( 'PreprocessorDefinitions',        ''  )

            # reformats/converts all the path entries according to a 'standard' format
            if ( True ):
                for name in vcpFiles.filtergroupNamesList:
                    filtergroup_nameLwr = name.lower()
                    vcpFiltergrp = vcpFiles.filtergroupNameValueDict[ filtergroup_nameLwr ]
                    for file_name in vcpFiltergrp.fileNamesList:
                        file_nameLwr = file_name.lower()
                        vcpFile = vcpFiltergrp.fileNameFileDict[ file_nameLwr ]
                        for config_name in vcpHdr.configurationFullNamesList:
                            config_nameLwr = config_name.lower()
                            if ( vcpFile.fileConfigNameSectionsDict.has_key( config_nameLwr ) ):
                                vcpFilecfg = vcpFile.fileConfigNameSectionsDict[ config_nameLwr ]
                                for tool_name in vcpFilecfg.toolNamesList:
                                    vcpTool = vcpFilecfg.toolNameSectionsDict[ tool_name ]
                                    for entryName in vcpTool.entryNamesList:
                                        entryValue = vcpTool.entryNameValueDict[ entryName ]
                                        if ( entryValue and g_mapPathEntries.has_key( entryName ) ):
                                            entryValue = FileUtils.normPath( entryValue, app.options.unixStyle, g_keepFirstDot_standard, g_MinPathIsDot_True, g_IsDirForSure_ChkDot )
                                            entryValue = DspFile.replaceCompilerTextTuple( entryValue, replaceCompilerTuple )
                                            vcpTool.entryNameValueDict[ entryName ] = entryValue

        return ( vcpHdr, vcpFiles )

    def getIndent( self, size ):
        indent = ''
        if ( 0 < size ):
            for x in range( size - 1 ):
                indent = indent + '\t'
        return indent

    def writelineEntriesVcprojAsStruct( self, vcpHdr, vcpFilesTemplate, newCompiler, vcpFilesOrg = None ):
        # Note part of the conversion work is already done by writelineEntriesVcprojAsStruct
        # because it does not write what is not accepted by that compiler's version

        # oldCompiler is unused

        # Important:
        #   vcpFilesTemplate is used to keep the same files entries as the source master file ( usually the dsp file ) ...
        #   .... but their content is given by vcpFilesOrg

        if ( g_printFilterGroupTrees and self.isFileIn2() ):
            print 'writelineEntriesVcprojAsStruct: file: %s' % self.filetitle
            vcpFilesTemplate.printChildren( '.', 'vcpFilesTemplate' )
            print 'writelineEntriesVcprojAsStruct: file: %s' % self.filetitle
            vcpFilesOrg.printChildren( '.', 'vcpFilesOrg' )

        # no other org file if not specified
        if ( not vcpFilesOrg ):
            vcpFilesOrg = vcpFilesTemplate

        if ( 0 == len( vcpHdr.configurationFullNamesList ) ):
            raise Exception( 'updateSouceEntriesVcprojAsStruct: vcpHdr.configurationFullNamesList is empty !' )

        #oldCompilerVersion = g_mapCompilerNameVersion[ oldCompiler ]
        newCompilerVersion = g_mapCompilerNameVersion[ newCompiler ]

        lines = []

        isVc71 = ( newCompiler == compilerVc71 )

        if ( isVc71 ):
            line = '<?xml version="%s" encoding="%s"?>\n' % ( vcpHdr.version_xml, vcpHdr.encoding_xml )
        else:
            line = '<?xml version="%s" encoding = "%s"?>\n' % ( vcpHdr.version_xml, vcpHdr.encoding_xml )
        lines.append( line )

        lines.append( '<VisualStudioProject\n' )

        #line = '\tProjectType=\"%s\"\n' % ( vcpHdr.projectType )
        #lines.append( line )
        #
        #line = '\tVersion=\"%s\"\n' % vcpHdr.version_vc_project
        #lines.append( line )
        #
        #line = '\tName=\"%s\"\n' % vcpHdr.trueProjectName
        #lines.append( line )

        # general section header
        for entryName in vcpHdr.entryNamesList:
            entryValue = vcpHdr.entryNameValueDict[ entryName ]
            if ( entryName == 'Version' and entryValue != vcpHdr.version_vc_project ):
                raise Exception( 'writelineEntriesVcprojAsStruct: Version is incompatible with vcpHdr.entryNameValueDict[ \'Version\' ].  It should be: %s == %s' % ( entryValue, vcpHdr.version_vc_project ) )
            line = '\t%s=\"%s\"\n' % ( entryName, entryValue )
            lines.append( line )
        lines[-1] = lines[-1].rstrip() + '>\n'


        lines.append( '\t<Platforms>\n' )

        lines.append( '\t\t<Platform\n' )

        line = '\t\t\tName=\"%s\"/>\n' % vcpHdr.platformName
        lines.append( line )

        lines.append( '\t</Platforms>\n' )

        lines.append( '\t<Configurations>\n' )


        for configFullName in vcpHdr.configurationFullNamesList:
            configFullNameLwr = configFullName.lower()
            vcpCfg = vcpHdr.configurationsFullNameSectionsDict[ configFullNameLwr ]

            lines.append( '\t\t<Configuration\n' )

            # configuration header
            for entryName in vcpCfg.entryNamesList:
                entryValue = vcpCfg.entryNameValueDict[ entryName ]
                line = '\t\t\t%s=\"%s\"\n' % ( entryName, entryValue )
                lines.append( line )
            lines[-1] = lines[-1].rstrip() + '>\n'

            # Tools
            for vcpToolName in vcpCfg.toolNamesList:
                vcpTool = vcpCfg.toolNameSectionsDict[ vcpToolName ]

                if ( compilerVersionVc71 <= newCompilerVersion or \
                        not g_mapToolsOnlyVc71.has_key( vcpTool.tool_name ) ):

                    # first check if we have some entries of this tools to write
                    toAddTool = False
                    for entryName in vcpTool.entryNamesList:
                        if ( compilerVersionVc71 <= newCompilerVersion or \
                                not g_mapToolEntriesOnlyVc71.has_key( entryName ) ):
                            toAddTool = True
                            break

                    if ( toAddTool ):
                        lines.append( '\t\t\t<Tool\n' )

                        for entryName in vcpTool.entryNamesList:
                            if ( compilerVersionVc71 <= newCompilerVersion or \
                                    not g_mapToolEntriesOnlyVc71.has_key( entryName ) ):
                                entryValue = vcpTool.entryNameValueDict[ entryName ]
                                line = '\t\t\t\t%s=\"%s\"\n' % ( entryName, entryValue )
                                lines.append( line )
                        lines[-1] = lines[-1].rstrip() + '/>\n'

            lines.append( '\t\t</Configuration>\n' )

        lines.append( '\t</Configurations>\n' )


        if ( compilerVersionVc71 <= newCompilerVersion ):
            lines.append( '\t<References>\n' )
            lines.append( '\t</References>\n' )

        # all the groups here !
        #lines.append( '\t<Files>\n' )
        self.writelineEntriesFilesFilterGroups( lines, vcpFilesTemplate, newCompiler, vcpFilesOrg )
        #lines.append( '\t</Files>\n' )

        lines.append( '\t<Globals>\n' )

        lines.append( '\t</Globals>\n' )

        lines.append( '</VisualStudioProject>\n' )

        self.lines = lines

        return

    def writelineEntriesFilesFilterGroups( self, lines, vcpFilesTemplate, newCompiler, vcpFilesOrg, parent = None, indent = '\t' ):
        newCompilerVersion = g_mapCompilerNameVersion[ newCompiler ]

        # vcpFilesTemplate is used to keep the same files entries as the source master file ( usually the dsp file )
        #  ( note: vcpFilesTemplate here, not vcpFilesOrg ) ...

        if ( not parent ):
            filtergroup = vcpFilesTemplate
        else:
            filtergroup = parent

        filtergroupName      = filtergroup.name
        filtergroupNameLwr   = filtergroupName.lower()

        if ( filtergroup.isFiles ):
            lines.append( indent + '<Files>\n' )
        else:
            lines.append( indent + '<Filter\n' )

            # filter group header
            line = 'Name=\"%s\"\n' % ( filtergroup.name )
            lines.append( indent + '\t' + line )
            line = 'Filter=\"%s\"\n' % ( filtergroup.value )
            lines.append( indent + '\t' + line )
            lines[-1] = lines[-1].rstrip() + '>\n'



        # first the subgroups (the subfolders), then the content of this group (the files)

        # here the recursion - after writing the file sections of itself
        if ( filtergroup.hasChildren() ):

            # the order from the 'master'
            childrenListSize = len( filtergroup.childrenList )
            for k in range( childrenListSize ):
                filtergroupData     = filtergroup.childrenList[ k ]
                filtergroupName     = filtergroupData.name
                filtergroupNameLwr  = filtergroupName.lower()

                if ( vcpFilesTemplate.filtergroupNameValueDict.has_key( filtergroupNameLwr ) ):
                    filtergroupChild = vcpFilesTemplate.filtergroupNameValueDict[ filtergroupNameLwr ]
                else:
                    raise Exception( 'writelineEntriesFilesFilterGroups: parent has not been provided by vcpFilesTemplate. Look into the code: the key for \'%s\' should be in this structure' % filtergroup.name )

                # .... but their content is given by vcpFilesOrg ( note: vcpFilesOrg here, not vcpFilesTemplate )
                # we prefere to use vcpFilesTemplate ( so the dsp file is the Template )
                #if ( vcpFilesTemplate.filtergroupNameValueDict.has_key( filtergroupNameLwr ) ):
                #    filtergroupChild = vcpFilesTemplate.filtergroupNameValueDict[ filtergroupNameLwr ]
                #else:
                #    if ( vcpFilesOrg and vcpFilesOrg.filtergroupNameValueDict.has_key( filtergroupNameLwr ) ):
                #        filtergroupChild = vcpFilesOrg.filtergroupNameValueDict[ filtergroupNameLwr ]
                #    else:
                #        raise Exception( 'writelineEntriesFilesFilterGroups: parent has not been provided by vcpFilesTemplate. Look into the code: the key for \'%s\' should be in this structure' % filtergroup.name )

                self.writelineEntriesFilesFilterGroups( lines, vcpFilesTemplate, newCompiler, vcpFilesOrg, filtergroupChild, indent + '\t' )


        # writes all the <File  > </File> sections for the 'current' Files/Filter(group) section
        self.writelineFileEntries( lines, vcpFilesTemplate, newCompiler, vcpFilesOrg, filtergroup, indent + '\t' )


        if ( filtergroup.isFiles ):
            lines.append( indent + '</Files>\n' )
        else:
            lines.append( indent +  '</Filter>\n' )

        return

    def writelineFileEntries( self, lines, vcpFilesTemplate, newCompiler, vcpFilesOrg, parent, indent ):
        newCompilerVersion = g_mapCompilerNameVersion[ newCompiler ]

        filtergroup = parent
        filtergroupNameLwr = filtergroup.name.lower()
        if ( vcpFilesOrg.filtergroupNameValueDict.has_key( filtergroupNameLwr ) ):
            filtergroupChildOrg = vcpFilesOrg.filtergroupNameValueDict[ filtergroupNameLwr ]
        else:
            filtergroupChildOrg = None

        indent = indent

        # File
        for filename in filtergroup.fileNamesList:
            filenameLwr = filename.lower()
            vcpFile = filtergroup.fileNameFileDict[ filenameLwr ]
            vcpFileOrg = None

            #.... but their content is given by vcpFilesOrg ( note: vcpFiles here, not vcpFilesTemplate )
            if ( g_uses_FileConfiguration_infos_from_original_file ):
                if ( filtergroupChildOrg and filtergroupChildOrg.fileNameFileDict.has_key( filenameLwr ) ):
                    vcpFileOrg = filtergroupChildOrg.fileNameFileDict[ filenameLwr ]

            lines.append( indent + '<File\n' )

            # file header
            # standard format
            vcpFile.file_relativepath = FileUtils.normPath( vcpFile.file_relativepath, app.options.unixStyle, g_KeepFirstDot_False, g_MinPathIsDot_True, g_IsDirForSure_False )

            line = '\tRelativePath=\"%s\"\n' % ( vcpFile.file_relativepath )
            lines.append( indent + line )
            lines[-1] = lines[-1].rstrip() + '>\n'

            # FileConfiguration
            # lets take them in the same sort order as
            #for fileConfig_name in vcpFile.fileConfigNameSectionsDict:

            # Note[*] IMPORTANT: because the <FileConfiguration section information
            # cannot easily ( and maybe it is impossible ) be calcultated from the dsp file
            # we use the original one for the entries that were existing in the original vcproj file
            # .... but their content is given by vcpFilesOrg ( note: vcpFiles here, not vcpFilesTemplate )
            # we prefere to use vcpFilesTemplate ( so the dsp file is the Template )
            if ( vcpFileOrg ):
                vcpFile = vcpFileOrg

            for fileConfig_name in vcpFile.fileConfigNamesList:
                fileConfig_nameLwr = fileConfig_name.lower()
                vcpFilecfg = vcpFile.fileConfigNameSectionsDict[ fileConfig_nameLwr ]

                #appType = self.appType
                #isDebug = ( config_nameLwr.find( 'debug' ) != -1 )

                # first check if we have some tools configuration to write
                toAddTools = False
                for tool_name in vcpFilecfg.toolNamesList:
                    vcpTool = vcpFilecfg.toolNameSectionsDict[ tool_name ]

                    if ( compilerVersionVc71 <= newCompilerVersion or \
                            not g_mapToolsOnlyVc71.has_key( vcpTool.tool_name ) ):
                        for entryName in vcpTool.entryNamesList:
                            if ( compilerVersionVc71 <= newCompilerVersion or \
                                    not g_mapToolEntriesOnlyVc71.has_key( entryName ) ):
                                toAddTools = True
                                break

                if ( toAddTools ):
                    lines.append( indent + '\t<FileConfiguration\n' )

                    # fileConfig header
                    line = '\t\tName=\"%s\"\n' % ( vcpFilecfg.fileConfig_name )
                    lines.append( indent + line )
                    # error !
                    #for entryName in vcpFilecfg.entryNamesList:
                    #    entryValue = vcpFilecfg.entryNameValueDict[ entryName ]
                    #    line = '\t%s=\"%s\"' % ( entryName, entryValue )
                    #    lines.append( indent + line + '\n' )
                    lines[-1] = lines[-1].rstrip() + '>\n'

                    # Tool
                    for tool_name in vcpFilecfg.toolNamesList:
                        vcpTool = vcpFilecfg.toolNameSectionsDict[ tool_name ]

                        if ( compilerVersionVc71 <= newCompilerVersion or \
                                not g_mapToolsOnlyVc71.has_key( vcpTool.tool_name ) ):
                            lines.append( indent + '\t\t<Tool\n' )

                            addedToolEntry = False

                            # Tool entries
                            for entryName in vcpTool.entryNamesList:
                                if ( compilerVersionVc71 <= newCompilerVersion or \
                                        not g_mapToolEntriesOnlyVc71.has_key( entryName ) ):
                                    entryValue = vcpTool.entryNameValueDict[ entryName ]

                                    # standard format
                                    if ( entryValue and g_mapPathEntries.has_key( entryName ) ):
                                        entryValue = FileUtils.normPath( entryValue, app.options.unixStyle, g_keepFirstDot_standard, g_MinPathIsDot_True, g_IsDirForSure_ChkDot )
                                        #entryValue = self.fixFilenamePostfix( entryValue, newCompiler, newCompiler, appType, isDebug, fileConfig_name )

                                    line = '\t\t\t%s=\"%s\"\n' % ( entryName, entryValue )
                                    lines.append( indent + line )
                                    addedToolEntry = True

                            if ( addedToolEntry ):
                                lines[-1] = lines[-1].rstrip() + '/>\n'
                            else:
                                lines[-1:] = [] # remove the entire tool !


                    lines.append( indent + '\t</FileConfiguration>\n' )

            lines.append( indent + '</File>\n' )

        return

    def process(self):
        self.removeUnwantedLines()

        self.getOutputTypeAndDir()
        self.modifyLines()

    def readTrueProjectName(self):
        # called only to the the trueProjectName ( the one inside the file itself )
        self.readlines()
        self.getOutputTypeAndDir()
        prjName = self.getTrueProjectName()
        return prjName

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
        self.isDebugCfg.append( configName.find( 'debug' ) != -1 )
        if ( configName.find( 'debug' ) != -1 ):
            self.c = 'd'
        else:
            self.c = 'r'
        return

    def getOutputTypeAndDir( self ):
        insideCfg = False
        addFound = False
        self.nCfg = -1
        self.projecName = ''
        self.projectType = ''
        self.configName = ''
        self.configFullName = ''
        self.configNameList = []
        self.configFullNameList = []
        self.hasCustomBuildList = []
        self.hasCustomBuildOutputDirList = []

        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n + 1

            #* exit after end of CFG section
            if ( line.find( '# Begin Target' ) != -1 ):
                insideCfg = False
                break

            if ( self.n < 6 ):
                # Microsoft Developer Studio Project File - Name="ApplicationKitDLL" - Package Owner=<4>
                m_trueproject = re_trueproject.match( line )
                if ( m_trueproject ):
                    self.trueProjectName = m_trueproject.group('trueProjectName')
                    self.setTrueProjectName( self.trueProjectName )
                    trueProjectNameLwr = self.trueProjectName.lower()
                    if ( trueProjectNameLwr.find( 'wiz' ) != -1 or trueProjectNameLwr.find( 'ins' ) != -1 ):
                        #msg = 'getOutputTypeAndDir: this application [%s] is probably an addins. File \'%s\' (%d). Line \'%s\'' % ( self.trueProjectName, self.filename, self.n, line.rstrip() )
                        msg = 'getOutputTypeAndDir: this application [%s] is probably an addins. File \'%s\' (%d). Line \'%s\'' % ( self.trueProjectName, self.filename, self.n, line.rstrip() )
                        self.isAddins = True
                        #print msg
                        #raise Exception( msg )
                    continue

                """
                #Microsoft made this not working either: a dll can have 'Application' as projectType see ImageFormats !
                # fortunately it doesn't really matters !
                m_targettype = re_targettype.match( line )
                if ( m_targettype ):
                    self.projectType = m_targettype.group( r'projectType' )
                    projectTypeLwr = self.projectType.lower()
                    if ( projectTypeLwr == 'generic project' ):
                        # this type has no output: is just a project to compile all its dependencies
                        self.outputExt = '.generic'
                        self.appType = enumAppTypeGeneric
                    elif ( projectTypeLwr == 'application' ):
                        self.outputExt = '.exe'
                        self.appType = enumAppTypeExe
                    elif ( projectTypeLwr == 'console application' ):
                        self.outputExt = '.exe'
                        self.appType = enumAppTypeExe
                    elif ( projectTypeLwr == 'static library' ):
                        self.outputExt = '.lib'
                        self.appType = enumAppTypeLib
                    elif ( projectTypeLwr == 'dynamic-link library' ):
                        self.outputExt = '.dll'
                        self.appType = enumAppTypeDll
                    elif ( projectTypeLwr == 'add-ins' ):
                        self.outputExt = '.awx'
                    else:
                        raise Exception( 'getOutputTypeAndDir: unknow project type [%s]. File \'%s\'. Line \'%s\'' % ( self.projectType, self.filename, line ) )
                    continue
                """

            #!IF  "$(CFG)" == "libAGG - Win32 GTK Debug"
            if ( line[0] == '!' ) :
                m_configuration = re_configuration.search( line )
                if ( m_configuration ):
                    insideCfg = True
                    self.nCfg += 1
                    self.OutputDirOutList  .append( '' )
                    self.PropOutputDirList .append( '' )
                    self.PropIntermeDirList.append( '' )

                    self.OutputDirOutCustomBuildList.append( '' )
                    self.hasCustomBuildList.append( False )
                    self.hasCustomBuildOutputDirList.append( False )
                    self.hasCustomBuild = False
                    self.hasCustomBuildOutputDir = False

                    self.projectName = m_configuration.group('projectName')
                    self.platform    = m_configuration.group('platform').rstrip()  # we don't really need it
                    self.configFullName  = m_configuration.group('configFullName') # GTK Debug
                    #self.configFullNameList.append( self.configName )
                    self.configFullNameList.append( self.configFullName )
                    if ( self.configFullName ):
                        splitlist = self.configFullName.split()
                        if ( 1 < len( splitlist ) ):
                            self.configName = ' '.join( splitlist[1:] )
                        else:
                            self.configName = self.configFullName
                        self.configNameList.append( self.configName )
                    else:
                        raise Exception( 'getOutputTypeAndDir: unable to split the configFullName (%s) in its parts )' % self.configFullName )

                    #m_confignamesplit = re_confignamesplit.match( self.configFullName )
                    #if ( m_confignamesplit ):
                    #    self.configName  = m_confignamesplit.group('configName')
                    #    self.configNameList.append( self.configName )
                    #else:
                    #    raise Exception( 'getOutputTypeAndDir: unable to split the configFullName (%s) in its parts )' % self.configFullName )

                    self.checkSetDebug()
                    self.isStaticCfg.append( self.configName.lower().find( 'static' ) != -1 ) # unused

                    # commented we don't need for now
                    #self.PropOutputDir  = self.PropOutputDirList [self.nCfg]
                    #self.PropIntermeDir = self.PropIntermeDirList[self.nCfg]
                    #self.OutputDirOut   = self.OutputDirOutList  [self.nCfg]
                    #self.OutputDirOutCustomBuild = self.OutputDirOutCustomBuildList[self.nCfg]

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
                    addFound = True

                    # try for dll or exe
                    if ( re_ADD_LINK32.match( line ) ):
                        if ( line.find( r'/dll' ) != -1 ):
                            self.appType = enumAppTypeDll
                            self.outputExt = '.dll'
                            pass
                        self.extractMainOutDir( line )
                        continue

                    # try for lib
                    elif ( re_ADD_LIB32.match( line ) ):
                        #isStaticlib = True
                        self.appType = enumAppTypeLib
                        self.outputExt = '.lib'
                        self.extractMainOutDir( line )
                        continue

                elif ( re_dsp_custom_build_basic_beg.match( line ) ):
                    self.checkCustomBuild( False )

                #if ( re_LIB32_static.match( line ) ):
                #    self.appType = enumAppTypeLib
                #    self.outputExt = '.lib'
                #    isStaticlib = True
                #    continue


        pass # end for

        if ( self.appType == enumAppTypeNone ):
            self.appType = enumAppTypeExe
            if ( self.outputExt == '' ):
                if ( addFound ):
                    # should be already assigned !
                    msg = 'WARNING: the file \'%s\' has \'/out:\' with default extension not assigned yet in the configuration \'%s\'. The extension \'%s\' will be assigned.' % ( self.filename, self.configName, '.exe' )
                    print msg
                self.outputExt = '.exe'
            #msg = 'WARNING: the file \'%s\' has no type assigned.' % ( self.filename )
            #raise Exception( msg )

        return

    def modifyLines( self ):
        self.nCfg = -1
        #insideCfg = False
        self.isDebugCfg  = []
        self.c = ''
        self.isStaticCfg = []
        self.projecName = ''
        self.projectType = ''
        self.configName = ''
        self.configFullName = ''
        self.configNameList = []
        self.configFullNameList = []
        #self.hasCustomBuildList = [] # no !
        #self.hasCustomBuildOutputDirList = [] # no !
        self.hasCustomBuild = False
        self.hasCustomBuildOutputDir = False

        state = 0
        for n in range( len(self.lines) ):
            line = self.lines[n]
            self.n = n + 1

            if ( state == 0 ):
                if ( line.find( '# Begin Target' ) != -1 ):
                    #insideCfg = False
                    state = 1
                    #break
                    continue

                #!IF  "$(CFG)" == "ApplicationKit - Win32 Release"
                if ( line[0] == '!' ):
                    m_configuration = re_configuration.search( line )
                    if ( m_configuration ):
                        insideCfg = True
                        self.nCfg += 1
                        self.projectName = m_configuration.group('projectName')
                        self.platform    = m_configuration.group('platform').rstrip() # we don't really need it
                        self.configFullName  = m_configuration.group('configFullName')
                        #m_confignamesplit = re_confignamesplit.match( self.configFullName )

                        if ( self.configFullName ):
                            splitlist = self.configFullName.split()
                            if ( 1 < len( splitlist ) ):
                                self.configName = ' '.join( splitlist[1:] )
                            else:
                                self.configName = self.configFullName
                            self.configNameList.append( self.configName )
                        else:
                            raise Exception( 'modifyLines: unable to split the configFullName (%s) in its parts )' % self.configFullName )

                        #if ( self.configFullName ):
                        #    self.configName  = m_confignamesplit.group('configName')
                        #    self.configNameList.append( self.configName )
                        #else:
                        #    raise Exception( 'modifyLines: unable to split the configFullName (%s) in its parts )' % self.configFullName )
                        #continue # why this was here ???

                        self.checkSetDebug()
                        self.isStaticCfg.append( self.configName.lower().find( 'static' ) != -1 ) # unused

                        self.PropOutputDir  = self.PropOutputDirList [self.nCfg]
                        self.PropIntermeDir = self.PropIntermeDirList[self.nCfg]
                        self.OutputDirOut   = self.OutputDirOutList  [self.nCfg]

                        self.hasCustomBuild = self.hasCustomBuildList[self.nCfg]
                        self.hasCustomBuildOutputDir = self.hasCustomBuildOutputDirList[self.nCfg]
                        # self.OutputDirOutCustomBuild = self.OutputDirOutCustomBuildList[self.nCfg]
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

                        elif ( re_dsp_custom_build_basic_beg.match( line ) ):
                            if ( self.hasCustomBuildOutputDirList[self.nCfg] ):
                                self.checkCustomBuild( True )

                    if ( changed ):
                        line = StringUtils.stripSpacesInExcess( line )
                        self.lines[n] = line

            elif ( state == 1 ):
                # we parse this only to reformat the entries
                m_dsp_source_basic = re_dsp_source_basic.match( line )
                if ( m_dsp_source_basic ):
                    m_dsp_source = re_dsp_source.match( line )
                    if ( m_dsp_source ):
                        source = m_dsp_source.group( 'sourcename' )
                        source = FileUtils.normPath( source, g_internal_unixStyle )

                        # reformat the entry in a 'standard' way
                        source = FileUtils.normPath( source, app.options.unixStyle, g_KeepFirstDot_False, g_MinPathIsDot_True, g_IsDirForSure_False )
                        #line = 'SOURCE=\"%s\"\n' % source # which one ?
                        line = 'SOURCE=%s\n' % source
                        self.lines[n] = line
                    else:
                        raise Exception( 'getSouceEntriesDsp: reading source but not source + infos. File: \'%s\'. Line[%d]: \'%s\'' % ( self.filename, self.n, line.rstrip() ) )
                    continue

                pass
        return

    def getPostFixIndex( filename, compiler = compilerVc6 ):
        if ( not compiler ):
            # look for the compiler too
            cpl = compilerVc6
            if ( filename.find( compiler ) == -1 ):
                if ( filename.find( compilerVc6 ) != -1 ):
                    cpl = compilerVc6
                elif ( filename.find( compilerIcl7 ) != -1 ):
                    cpl = compilerIcl7
                elif ( filename.find( compilerVc70 ) != -1 ):
                    cpl = compilerVc70
                elif ( filename.find( compilerVc71 ) != -1 ):
                    cpl = compilerVc71
                else:
                    cpl = compilerVc6 # it doesn't matter in this case
            compiler = cpl
        ( stat, dbg ) = ( False, False )
        basetitle = filename
        i = basetitle.rfind( '_' )
        if ( i != -1 ):
            name = basetitle[:i]
            postfix = basetitle[i+1:]
            if ( postfix == 'd' or postfix == 's' or postfix == 'sd' or postfix == compiler ):
                basetitle = name

                if ( postfix == 's' or postfix == 'sd' ):
                    stat = True
                if ( postfix == 'd' or postfix == 'sd' ):
                    dbg  = True

                #j = filename.rfind( '_', i-1 )  # the start index specification DOESN'T WORK AT ALL
                j = basetitle.rfind( '_' )
                while ( j != -1 ):
                    name = basetitle[:j]
                    postfix = filename[j+1:i]
                    if ( postfix == compiler or postfix == compilerVc6 or postfix == compilerIcl7 or postfix == compilerVc70 or postfix == compilerVc71 ):
                        basetitle = name # fixed 2004/05
                        i = j
                        j = basetitle.rfind( '_' )
                    else:
                        break

                    # j = basetitle.rfind( '_' )
                    pass

                #i = j # fixed 2004/05
            else:
                if ( postfix == compiler or postfix == compilerVc6 or postfix == compilerIcl7 or postfix == compilerVc70 or postfix == compilerVc71 ):
                    basetitle = name
                i = len( basetitle )

        return ( ( i, basetitle, compiler ), ( stat, dbg ) )
    getPostFixIndex = staticmethod(getPostFixIndex)

    def getPostFix( self, compiler = compilerVc6 ):
        postfix = '_' + compiler
        if ( self.appType == enumAppTypeDll ):
            if ( self.isDebugCfg[self.nCfg] ):
                postfix += '_d'
        elif ( self.appType == enumAppTypeLib ):
            if ( self.isDebugCfg[self.nCfg] ):
                postfix += '_sd'
            else:
                postfix += '_s'
        return postfix

    def splitPostfixComponents( filename, compiler ):
        ( sp, sf ) = FileUtils.split( filename ) # do not use os.path implementation
        ( sb, se ) = FileUtils.splitext( sf )
        ( ( si, sm, cpl ), ( ss, sd ) ) = DspFile.getPostFixIndex( sb, compiler )
        smLwr = sm.lower()
        tup = ( ( sp, sf ), ( sb, se ), ( si, sm, smLwr, cpl ), ( ss, sd ) )
        return tup
    splitPostfixComponents = staticmethod(splitPostfixComponents)

    def getPostFix2( self, compiler, appType, isDebug ):
        postfix = '_' + compiler
        if ( appType == enumAppTypeDll ):
            if ( isDebug ):
                postfix += '_d'
        elif ( appType == enumAppTypeLib ):
            if ( isDebug ):
                postfix += '_sd'
            else:
                postfix += '_s'
        return postfix

    def fixFilenamePostfix( self, pathfilename, oldCompiler, compiler, appType, isDebug, config_name = '' ):
        if ( not app.options.fixFilenamePostfix ):
            return pathfilename

        if ( not self.filename ):
            # no changes
            return pathfilename

        if ( appType == enumAppTypeNone or appType == enumAppTypeUnknown ):
            if ( 0 < app.options.warning ):
                if ( not warning_unknown_configuration_type ):
                    warning_unknown_configuration_type = True
                    msg = 'WARNING: unknown configuration type (%d).  Configuration \'%s\'.  File \'%s\'. Please fix this manually.' % ( appType, config_name, self.filename )
                    print msg

        # looks for the mainFileTitleBase of both the current file and of pathfilename ( i.e. without any postfix )
        ( ( sp, sf ), ( sb, se ), ( si, sm, smLwr, cpl ), ( ss, sd ) ) = DspFile.splitPostfixComponents( self.filename, compiler )
        if ( not sm ):
            return pathfilename

        ( ( fp, ff ), ( fb, fe ), ( fi, fm, fmLwr, cpl ), ( fs, fd ) ) = DspFile.splitPostfixComponents( pathfilename, compiler )
        if ( not fm ):
            return pathfilename

        #if ( self.isFileIn2() ):
        #    msg = 'WARNING: [%s\n fp: %s\nff: %s\n fb: %s\nfe: %s\n] the entry has a postfix [ %s ] NOT different than the unexpected one [ %s ]. Configuration \'%s\'.  File \'%s\'.' % ( pathfilename, fp, ff, fb, fe, fm, sm, config_name, self.filename )
        #    print msg

        if ( fmLwr != smLwr ):
            return pathfilename

        # the right postfix
        postfix = self.getPostFix2( compiler, appType, isDebug )
        fn = fm + postfix + fe

        putPostfix = True
        if ( app.projectsNoPostfixList or app.projectsNoPostfixOutputList or app.projectsNoPostfixIfUnderCompilerDirList ):
            if ( self.isInProjectsNoPostfixList() or self.isInProjectsNoPostfixOutputList() or self.isInProjectsNoPostfixIfUnderCompilerDirList() ):
                putPostfix = False
        if ( putPostfix ):
            fn2 = fm + postfix + fe
        else:
            fn2 = fm + fe

        # not using FileUtils.split
        #if ( fp and ff ):
        #    sep = pathfilename[ len( fp ) ]
        #    pfn = fp + sep + fn
        #else:
        #    pfn = fn
        #
        # using FileUtils.split
        if ( fp ):
            pfn = fp + fn
            pfn2 = fp + fn2
        else:
            pfn = fn
            pfn2 = fn2

        if ( pathfilename != pfn2 ):
            if ( 0 < app.options.warning ):
                warn = True
                fforg = ff
                if ( oldCompiler != compiler ):
                    ff = ff.replace( oldCompiler, compiler )
                    if ( ff == fn2 ):
                        warn = False
                if ( warn ):
                    if ( 0 < self.n and self.n < len( self.lines ) ):
                        line = self.lines[ self.n - 1 ]
                        msg = 'WARNING [fixFilenamePostfix]: the entry has a postfix [ %s ] different than the expected one [ %s ]. This will be fixed.  Configuration \'%s\'.  File \'%s\' (%d). Line: %s' % (  ff, fn2, config_name, self.filename, self.n, line.rstrip() )
                    else:
                        msg = 'WARNING [fixFilenamePostfix]: the entry has a postfix [ %s ] different than the expected one [ %s ]. This will be fixed.  Configuration \'%s\'.  File \'%s\'.' % (  ff, fn2, config_name, self.filename )
                    print msg

        return pfn2

    def librariesChangePostfix( self, libSlist, oldCompiler, compiler, appType, isDebug, config_name = '' ):
        # used for AdditionalDependencies in vc7x
        # return libSlist # uncommenting this disable the function

        ( ( sp, sf ), ( sb, se ), ( si, sm, smLwr, cpl ), ( ss, sd ) ) = DspFile.splitPostfixComponents( self.filename, compiler )
        if ( not sm ):
            return libSlist

        hadNewline = False
        if ( libSlist and libSlist[-1] == '\n' ):
            hadNewline = True

        # if some options works only on the first part
        afterOption = ''
        libSlist2 = libSlist
        p = libSlist2.find( '/' )
        if ( p != -1 ):
            # some options
            afterOption = libSlist2[p:]     # '/' included
            libSlist2 = libSlist2[:p] # just before '/'

        ls = libSlist2.split( ' ' )
        libDict = {}
        libList = []
        lmList = []
        lmLwrList = []
        for lib in ls:
            lib = lib.strip()
            libLwr = lib.lower()

            # it just would be compiler if we knew for sure that lib has the right postfix
            ( ( lp, lf ), ( lb, le ), ( li, lm, lmLwr, cpl ), ( ls, ld ) ) = DspFile.splitPostfixComponents( lib, '' )
            if ( not lm ):
                continue

            libList.append( lib )
            lmLwr = lm.lower()
            lmLwrList.append( lmLwr )
            libDict[ lmLwr ] = ( lm, le, lib )

        # first we see if the current project is in the projects list of app.librariesChangePostfixListLwr
        libSlistNew = ''
        for projLwr in app.librariesChangePostfixListLwr:
            # looks for the mainFileTitleBase of both the current file and of projLwr ( i.e. without any postfix )

            ( ( pp, pf ), ( pb, pe ), ( pi, pm, pmLwr, cpl ), ( ps, pd ) ) = DspFile.splitPostfixComponents( projLwr, compiler )
            if ( pmLwr and pmLwr == smLwr ):
                # ok expected project

                libListNew = []
                libPsfxList = app.librariesChangePostfixDictList[ projLwr ]
                libPsfxDict = app.librariesChangePostfixDictDict[ projLwr ]

                for lmLwr in lmLwrList:
                    ( lm, le, lib )  = libDict[ lmLwr ]
                    if ( libPsfxDict.has_key( lmLwr ) ):
                        # finally found the wanted match
                        ( ( xm, xe, xlib ), ( xs, xd ) ) = libPsfxDict[ lmLwr ]

                        # if we specified the extension, this means we restrict ourselves only to lib of that kind
                        if ( xe and xe != le ):
                            libListNew.append( lib )
                        else:
                            # fix the name

                            # libFixed = self.fixFilenamePostfix( lib, compiler, compiler, appType, isDebug, config_name )
                            if ( xs ):
                                appType = enumAppTypeLib
                            # isDebug = xd # No! Mistake here: we don't need to specify '_d' in the list (better not). But the config ( debug/non ) tells which lib we want

                            postfix = self.getPostFix2( compiler, appType, isDebug )
                            ln = lm + postfix + le
                            ( lp, lf ) = FileUtils.split( lib )
                            if ( lp ):
                                pfn = lp + ln
                            else:
                                pfn = ln

                            if ( lib != pfn ):
                                if ( 0 < app.options.warning ):
                                    warn = True
                                    lforg = lf
                                    if ( oldCompiler != compiler ):
                                        lf = lf.replace( oldCompiler, compiler )
                                        if ( lf == ln ):
                                            warn = False
                                    if ( warn ):
                                        if ( 0 < self.n and self.n < len( self.lines ) ):
                                            line = self.lines[ self.n - 1 ]
                                            msg = 'WARNING [librariesChangePostfix]: the entry has a postfix [ %s ] different than the expected one [ %s ]. This will be fixed.  Configuration \'%s\'.  File \'%s\' (%d). Line: %s' % (  lf, ln, config_name, self.filename, self.n, line.rstrip() )
                                        else:
                                            msg = 'WARNING [librariesChangePostfix]: the entry has a postfix [ %s ] different than the expected one [ %s ]. This will be fixed.  Configuration \'%s\'.  File \'%s\'.' % (  lf, ln, config_name, self.filename )
                                        print msg

                            lib = pfn

                            libListNew.append( lib )

                    else:
                        libListNew.append( lib )

                libSlistNew = ' '.join( libListNew )

                # this project found in list and managed, then exit
                break

        if ( libSlistNew ):
            list = libSlistNew + ' ' + afterOption.rstrip()
        else:
            list = libSlist2 + ' ' + afterOption.rstrip()
        list = list.rstrip()
        if ( hadNewline ):
            list += '\n'

        return list

    def isInProjectsNoPostfixList( self ):
        isInList = False

        if ( app.projectsNoPostfixList ):

            ( ( sp, sf ), ( sb, se ), ( si, sm, smLwr, cpl ), ( ss, sd ) ) = DspFile.splitPostfixComponents( self.filename, self.compiler )
            if ( sm ):
                if ( app.projectsNoPostfixMainNameLwrDict.has_key( smLwr ) ):
                    isInList = True

        return isInList

    def isInProjectsNoPostfixOutputList( self ):
        isInList = False

        if ( app.projectsNoPostfixOutputList ):

            ( ( sp, sf ), ( sb, se ), ( si, sm, smLwr, cpl ), ( ss, sd ) ) = DspFile.splitPostfixComponents( self.filename, self.compiler )
            if ( sm ):
                if ( app.projectsNoPostfixOutputMainNameLwrDict.has_key( smLwr ) ):
                    isInList = True

        return isInList

    def isInProjectsNoPostfixIfUnderCompilerDirList( self ):
        isInList = False

        if ( app.projectsNoPostfixIfUnderCompilerDirList ):

            ( ( sp, sf ), ( sb, se ), ( si, sm, smLwr, cpl ), ( ss, sd ) ) = DspFile.splitPostfixComponents( self.filename, self.compiler )
            if ( sm ):
                if ( app.projectsNoPostfixIfUnderCompilerDirMainNameLwrDict.has_key( smLwr ) ):
                    isInList = True

        return isInList

    def translateConfigurationType( value ):
        #val = enumAppTypeUnknown

        # we use the same values:
        val = value
        return val
    translateConfigurationType = staticmethod(translateConfigurationType)

    def reformatDir( self, relpath ):
        # adds '_compiler/' to the relpath and removes a possible '/obj'
        relpath = FileUtils.normDir( relpath, g_internal_unixStyle )
        sep = FileUtils.getNormSep( g_internal_unixStyle )
        pvc6s = compilerVc6 + sep
        pvc60s = compilerVc6 + '0' + sep
        if ( relpath.find( pvc6s ) == -1 or relpath.find( pvc60s ) == -1 ):
            # nothing if we are already under a vc60 or vc6 path !
            if ( self.filename.find( pvc6s ) == -1 or self.filename.find( pvc60s ) == -1 ):
                # 'vc60/' not 'vc6/' ! also in any path !
                if ( self.filename.find( pvc6s ) != -1 ):
                    self.filename.replace( pvc6s, pvc60s )
            else:
                if ( relpath and relpath[0] != sep and not relpath.find( '..' ) == 0 ):  # i.e. not ( existing and at the beginning of the pahname )
                    relpath = compilerVc6 + sep + relpath[:]

        # 'vc60/' not 'vc6/' !
        if ( relpath.find( pvc6s ) != -1 ):
            relpath.replace( pvc6s, pvc60s )

        # eliminates '/obj' because at this point it is annoying
        relpath = StringUtils.replace( relpath, sep + 'obj', '' )

        return relpath

    def extractOutputIntermDir( self, line ) :
        m = re_output_or_intermed_dir.match( line )
        if ( m ):
            subdir = m.group('subdir')
            dirname = self.reformatDir( subdir )

            dirname = FileUtils.normPath( dirname, app.options.unixStyle, g_KeepFirstDot_False, g_MinPathIsDot_True, g_IsDirForSure_ChkDot )

            if ( re_intermed_dir.match( line ) ):
                self.PropIntermeDirList[self.nCfg] = dirname
            else:
                self.PropOutputDirList[self.nCfg] = dirname
        return

    def extractMainOutDir( self, line ):
        #if ( line.find( r'/out:' ) != -1 ):
        #if ( isCustomBuild ):
        #    self.extractMainOutDirCustomBuild( line )

        m_option_out_dir = re_option_out_dir_spaces.search( line )
        if ( not m_option_out_dir ):
            m_option_out_dir = re_option_out_dir_nospaces.search( line )
        if ( m_option_out_dir ):

            pathname = m_option_out_dir.group( 'pathname' )
            pathname = FileUtils.normPath( pathname, g_internal_unixStyle )

            # Lib
            dirname = os.path.dirname( pathname )
            dirname =  FileUtils.normDir( dirname, g_internal_unixStyle )

            dirname = FileUtils.normPath( dirname, app.options.unixStyle, g_KeepFirstDot_False, g_MinPathIsDot_True, g_IsDirForSure_ChkDot )

            self.OutputDirOutList[self.nCfg] = dirname

            # check for outputdir non congruent between different configurations
            if ( 0 < self.nCfg ):
                dirname0 = self.OutputDirOutList[0]
                d = dirname0.replace( self.configNameList[0], self.configName )
                if ( d != dirname ):
                    if ( 2 < app.options.warning ):
                        if ( not self.warning_done_extension_different_than_expected ):
                            self.warning_done_extension_different_than_expected = True
                            d = dirname.replace( self.configNameList[0], self.configName )
                            if ( d != dirname ):
                                msg = 'WARNING: \'/out:\' with relative path (%s) different than expected (%s). Configuration \'%s\' File \'%s\' (%d).  Line: %s!' % ( dirname, d, self.configName, self.filename, self.n, line.rstrip() )
                                print msg

            basetitle = os.path.basename( pathname )
            (basetitle,ext) = os.path.splitext( basetitle )
            if ( ext == '' ):
                msg = 'WARNING: \'/out:\' with no extension (%s) ! [ and the expected is (%s) ] in the configuration \'%s\'].  File \'%s\' (%d). Line: %s' % ( ext, self.outputExt, self.configName, self.filename, self.n, line.rstrip() )
                print msg
            else:
                # check for extension different than expected
                if ( ext != self.outputExt ):
                    # it is working right. But with this warning we see when this is happening
                    if ( 2 < app.options.warning ):
                        if ( not self.warning_done_extension_different_than_expected ):
                            self.warning_done_extension_different_than_expected = True
                            if ( self.outputExt == '' ):
                                msg = 'WARNING: \'/out:\' with extension (%s) but the expected is still undefined (%s) in the configuration \'%s\'. Fixed as \'%s\'.  File \'%s\' (%d). Line: %s' % (  ext, self.outputExt, self.configName, ext, self.filename, self.n, line.rstrip() )
                            else:
                                msg = 'WARNING: \'/out:\' with extension (%s) different than expected (%s) in the configuration \'%s\'. Fixed as \'%s\'.  File \'%s\' (%d). Line: %s' % ( ext, self.outputExt, self.configName, ext, self.filename, self.n, line.rstrip() )
                            print msg
                    self.outputExt = ext
            ( (ipf, basetitle, cpl), ( stat, dbg ) ) = DspFile.getPostFixIndex( basetitle )
            if ( len( basetitle ) ):
                self.mainFileTitleBase = basetitle
        else:
            # note that we self.checkCustomBuild only if we don't find any /out: in a '# ADD LINK' or '# ADD LIB' line
            self.OutputDirOutList[self.nCfg] = self.PropOutputDirList[self.nCfg]
            self.mainFileTitleBase = self.trueProjectName
            if ( self.appType == enumAppTypeNone ):
                self.appType = enumAppTypeExe
                if ( self.outputExt == '' ):
                    # should be already assigned !
                    self.outputExt = '.exe'
            if ( 0 < app.options.warning ):
                fn = self.OutputDirOutList[self.nCfg] + self.mainFileTitleBase + self.outputExt
                if ( fn ):
                    (fn,ext) = os.path.splitext( fn )
                    ( (ipf, basetitle, cpl), ( stat, dbg ) ) = DspFile.getPostFixIndex( fn )
                    if ( ipf != -1 ):
                        fn = fn[:ipf]
                    fn += self.getPostFix()
                    fn += ext
                msg = 'WARNING: No \'/out:\' option. It will be fixed as: \'/out:%s\' with assigned extension: \'%s\'.  Configuration \'%s\'.  File \'%s\' (%d). Line: %s' % ( fn, self.outputExt, self.configName, self.filename, self.n, line.rstrip() )
                print msg

        return

    def extractMainOutDirCustomBuild( self, line ):
        #if ( line.find( r'/out:' ) != -1 ):

        customBuildString = ' [Custom Build]'

        m_option_out_dir = re_option_out_dir_spaces.search( line )
        if ( not m_option_out_dir ):
            m_option_out_dir = re_option_out_dir_nospaces.search( line )
        if ( m_option_out_dir ):

            pathname = m_option_out_dir.group( 'pathname' )
            pathname = FileUtils.normPath( pathname, g_internal_unixStyle )

            # Lib
            dirname = os.path.dirname( pathname )
            dirname =  FileUtils.normDir( dirname, g_internal_unixStyle )

            dirname = FileUtils.normPath( dirname, app.options.unixStyle, g_KeepFirstDot_False, g_MinPathIsDot_True, g_IsDirForSure_ChkDot )

            self.OutputDirOutCustomBuildList[self.nCfg] = dirname

            # check for outputdir non congruent between different configurations
            if ( 0 < self.nCfg ):
                dirname0 = self.OutputDirOutCustomBuildList[0]
                d = dirname0.replace( self.configNameList[0], self.configName )
                if ( d != dirname ):
                    if ( 2 < app.options.warning ):
                        if ( not self.warning_done_extension_different_than_expected ):
                            self.warning_done_extension_different_than_expected = True
                            d = dirname.replace( self.configNameList[0], self.configName )
                            if ( d != dirname ):
                                msg = 'WARNING:%s \'/out:\' with relative path (%s) different than expected (%s). Configuration \'%s\' File \'%s\' (%d).  Line: %s!' % ( customBuildString, dirname, d, self.configName, self.filename, self.n, line.rstrip() )
                                print msg

            basetitle = os.path.basename( pathname )
            (basetitle,ext) = os.path.splitext( basetitle )
            if ( ext == '' ):
                msg = 'WARNING:%s \'/out:\' with no extension (%s) ! [ and the expected is (%s) ] in the configuration \'%s\'].  File \'%s\' (%d). Line: %s' % ( customBuildString, ext, self.outputExt, self.configName, self.filename, self.n, line.rstrip() )
                print msg
            else:
                # check for extension different than expected
                if ( ext != self.outputExtCustomBuild ):
                    # it is working right. But with this warning we see when this is happening
                    if ( 2 < app.options.warning ):
                        if ( not self.warning_done_extension_different_than_expected ):
                            self.warning_done_extension_different_than_expected = True
                            if ( self.outputExt == '' ):
                                msg = 'WARNING:%s \'/out:\' with extension (%s) but the expected is still undefined (%s) in the configuration \'%s\'. Fixed as \'%s\'.  File \'%s\' (%d). Line: %s' % (  customBuildString, ext, self.outputExtCustomBuild, self.configName, ext, self.filename, self.n, line.rstrip() )
                            else:
                                msg = 'WARNING:%s \'/out:\' with extension (%s) different than expected (%s) in the configuration \'%s\'. Fixed as \'%s\'.  File \'%s\' (%d). Line: %s' % ( customBuildString, ext, self.outputExtCustomBuild, self.configName, ext, self.filename, self.n, line.rstrip() )
                            print msg
                    self.outputExtCustomBuild = ext

            ( (ipf, basetitle, cpl), ( stat, dbg ) ) = DspFile.getPostFixIndex( basetitle )
            if ( len( basetitle ) ):
                self.mainFileTitleBaseCustomBuild = basetitle

        return

    def checkCustomBuild( self, changeLine ):
        n = self.n - 1
        insideCustomBuild = False
        linerule = ''
        lineruleNum = -1
        lineCustomBuildBegin = -1
        lineCustomBuildEnd = -1
        for p in range( len( self.lines ) - n - 2 ):  # -2 just for safety
            q = n + p
            line = self.lines[ q ]

            m_dsp_custom_build_basic_beg = re_dsp_custom_build_basic_beg.match( line )
            # Begin Custom Build - Creating static library libxml2_a.lib...
            if ( m_dsp_custom_build_basic_beg ):
                insideCustomBuild = True
                self.hasCustomBuild = True
                self.hasCustomBuildList[self.nCfg] = self.hasCustomBuild
                lineCustomBuildBegin = q
                continue

            if ( insideCustomBuild ):
                if ( re_dsp_custom_build_basic_lib.search( line ) ):
                    # No warning: we can have both: see e.g. libxml2.dsp
                    if ( self.appType != enumAppTypeNone and self.appType != enumAppTypeLib ):
                        pass # pass!  do not continue!

                elif ( re_dsp_custom_build_basic_dll.search( line ) ):
                    if ( self.appType != enumAppTypeNone and self.appType != enumAppTypeLib ):
                        # False: we can have both: see e.g. libxml2.dsp
                        pass # pass!  do not continue!

                if ( line.find( '/out' ) != -1 ):
                    self.hasCustomBuildOutputDir = True
                    self.hasCustomBuildOutputDirList[self.nCfg] = self.hasCustomBuildOutputDir
                    self.extractMainOutDirCustomBuild( line )
                    continue

                m_custom_build_rule = re_custom_build_rule.match( line )
                if ( m_custom_build_rule ):
                    linerule = line
                    lineruleNum = q
                    #li = self.lines[ q ]
                    continue

            m_dsp_custom_build_basic_end = re_dsp_custom_build_basic_end.match( line )
            # Begin Custom Build - Creating static library libxml2_a.lib...
            if ( m_dsp_custom_build_basic_end ):
                lineCustomBuildEnd = q
                if ( not insideCustomBuild ):
                    msg = 'ERROR: Found \'# End Custom Build\' without \'# Begin Custom Build\'. Configuration \'%s\'.   File \'%s\' (%d). Line: %s' % ( self.configName, self.filename, self.n, line.rstrip() )
                    raise Exception( msg )
                #li = self.lines[ lineruleNum ]
                break

            if ( line[0] == '!' ) :
                if ( line.find( '!IF' ) == 0 or line.find( '!ENDIF' ) == 0 or line.find( '!ELSEIF' ) == 0 ):
                    if ( self.hasCustomBuildList[self.nCfg] ):
                        msg = 'ERROR: Found end of configuration before \'# End Custom Build\'. Configuration \'%s\'.   File \'%s\' (%d). Line: %s' % ( self.configName, self.filename, self.n, line.rstrip() )
                        raise Exception( msg )
                    break
                else:
                    msg = 'WARNING: Unexpected format for this line. Please improve the code script or check the changes to \'/out:\' made in this file. Configuration \'%s\'.   File \'%s\' (%d). Line: %s' % ( self.configName, self.filename, self.n, line.rstrip() )
                    print msg
                    #raise Exception( msg )
            pass

        if ( changeLine ):
            if ( False ):
                fn = self.OutputDirOutCustomBuildList[self.nCfg] + self.mainFileTitleBaseCustomBuild + self.outputExtCustomBuild
                if ( fn ):
                    (fn,ext) = os.path.splitext( fn )
                    ( (ipf, basetitle, cpl), ( stat, dbg ) ) = DspFile.getPostFixIndex( fn )
                    if ( ipf != -1 ):
                        fn = fn[:ipf]
                    fn += self.getPostFix()
                    #fn += ext

                c1 = fn.rfind( '\\' )
                c2 = fn.rfind( '/' )
                if ( c1 != -1 or c2 != -1 ):
                    c = max( c1, c2 )
                    bn = fn[c+1:]
                else:
                    bn = fn

            b = lineCustomBuildBegin
            e = lineCustomBuildEnd

            self.checkCustomBuildReplaceTitlebaseCompilerVersion( b, e, self.mainFileTitleBase, self.outputExt )
            self.checkCustomBuildReplaceTitlebaseCompilerVersion( b, e, self.mainFileTitleBaseCustomBuild, self.outputExtCustomBuild )

            if ( False ):
                lin = self.lines[ q ]
                lin = re_option_out_dir.sub( fn, line )
                self.lines[ q ] = lin

                # go back to the rule line and update it !
                lin = self.lines[ lineruleNum ]
                #re_option_out_dir = re_option_out_dir_spaces
                #re_option_out_dir = re_option_out_dir_nospaces
                m_custom_build_rule = re_custom_build_rule.match( lin )
                if ( m_custom_build_rule ):
                    lin = re_custom_build_rule.sub( fn, lin )
                    self.lines[ lineruleNum ] = lin
                else:
                    raise Exception( 'wrong code: we should match re_custom_build_rule!' )
                pass

        return

    def checkCustomBuildReplaceTitlebaseCompilerVersion( self, begin, end, titlebase, extbase ):
        postfix = self.getPostFix()
        basename = titlebase + postfix
        #basename = titlebase + postfix + extbase

        # update all lines inside Custom Build section
        for q in range( begin, end + 1 ):
            #q = n + p
            lin = self.lines[ q ]

            lin = lin.rstrip() # get rid of last '\n'
            # we look for only *one* occurrence per line
            # if necessary we will improve the code in the future and look for more of them
            titlebaseLwr = titlebase.lower()
            lent = len( titlebaseLwr )
            linLwr = lin.lower()

            changed = False
            k = 0
            k = linLwr.find( titlebaseLwr, k )
            while ( k != -1 ):
                u = linLwr.find( '.', k )
                if ( u != -1 ):
                    b1 = linLwr[k:u]
                    ( (ipf2, bt2, cpl), ( stat, dbg ) ) = DspFile.getPostFixIndex( b1 )
                    if ( bt2 == titlebaseLwr ):
                        lin = lin[:k] + basename + lin[u:]
                        changed = True
                k = k + lent
                k = linLwr.find( titlebaseLwr, k )
            if ( changed ):
                lin = lin + '\n'
                self.lines[ q ] = lin

        return

    def addReformatOutputIntermediateDirs( self, line, subdir ):
        # reformat a line for Intermediate/Output directory - never remove it !
        changeSomething = ( app.options.reformatOutputIntermediateDirs == 1 )

        if ( changeSomething ):
            dirname = self.reformatDir( subdir ) # for debug

            dirname = FileUtils.normPath( dirname, app.options.unixStyle, g_KeepFirstDot_False, g_MinPathIsDot_True, g_IsDirForSure_ChkDot )

            if ( re_intermed_dir.match( line ) ):
                if ( self.PropIntermeDir != dirname ):
                    raise Exception( 'self.PropIntermeDir != dirname i.e. \'%s\' != \'%s\'' % ( self.PropIntermeDir, dirname) )
            else:
                if ( self.PropOutputDir != dirname ):
                    raise Exception( 'self.PropOutputDir != dirname i.e. \'%s\' != \'%s\'' % ( self.PropOutputDir, dirname) )
            line = StringUtils.replace( line, subdir, dirname )
        return line

    def changeOptionsCpp( self, line ):
        self.storedOptions = []

        changeSomething =   ( app.options.reformatOptionOutput  [self.c] != 0 ) or \
                            ( app.options.reformatOptionPdb     [self.c] != 0 ) or \
                            ( app.options.reformatOptionBrowse  [self.c] != 0 )
        if ( changeSomething ):
            if ( self.addKind == enum_ADD_CPP ):
                # the order of the following calls counts ( maybe not anymore )
                line = self.storeRemoveOptionOutputDir( line )
                line = self.storeRemoveOptionPdb( line )
                line = self.storeRemoveOptionBrowse( line )
                optionsList = [ '/D' ]
                index = self.findLastIndexInList( optionsList, line, False )
                if ( index == -1 ):
                    raise Exception( 'ADD CPP line without any /D option. Please improve the code or check the line.' )
            elif ( self.addKind == enum_SUBTRACT_CPP ):
                # the order of the following calls counts ( maybe not anymore )
                line = self.storeRemoveOptionBrowse( line )
                optionsList = [ '/Wx' ]
                index = self.findLastIndexInList( optionsList, line, True )

            line = self.addStoredOptions( line, index, optionsList )

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

                line = self.addStoredOptions( line, index, optionsList )

        return line

    def changeOptionsLnk( self, line ):
        self.storedOptions = []

        changeSomething =   ( app.options.reformatOptionOutput[self.c] == 1 ) or \
                            ( app.options.reformatOptionPdb   [self.c] != 0 )

        if ( changeSomething ):
            if ( self.addKind == enum_ADD_LINK32 ):
                # the order of the following calls counts ( maybe not anymore )
                # '/pdbtype:' goes after '/out:'
                optionsList = [ '/nologo', '/entry:', '/subsystem:', '/dll', '/profile', '/debug', '/machine:', '/implib:', '/out:', '/pdbtype:', '/libpath:' ]
                #app.logFilePrintLine( line )
                line = self.storeRemoveOptionOutputDir( line )
                #app.logFilePrintLine( line )
                line = self.storeRemoveOptionPdb( line )
                #app.logFilePrintLine( line )
                index = self.findLastIndexInList( optionsList, line, True )
                if ( index == -1 ):
                    raise Exception( 'ADD LINK32 line without any option between %s. Please improve the code or check the line.' % optionsList )
            elif ( self.addKind == enum_SUBTRACT_LINK32 ):
                 # the order of the following calls counts ( maybe not anymore )
                line = self.storeRemoveOptionPdb( line )
                optionsList = [ '/incremental:', '/map', '/pdb:' ]
                index = self.findLastIndexInList( optionsList, line, True )

            #app.logFilePrintLine( line )
            line = self.addStoredOptions( line, index, optionsList )
            #app.logFilePrintLine( line )
            # whith this new function we can probalby remove the self.findLastIndexInList
            line = self.moveOptionsProperOrder( line, optionsList )
            #app.logFilePrintLine( line )

            # # ADD LINK32 wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"libxml2\libxml2_vc6_d.dll" /pdbtype:sept
            if ( app.librariesChangePostfixListLwr ):
                line = self.librariesChangePostfix( line, self.compiler, self.compiler, self.appType, self.isDebugCfg[self.nCfg], self.configFullName )

        return line

    def changeOptionsLib( self, line ):
        self.storedOptions = []

        changeSomething =   ( app.options.reformatOptionOutput[self.c] == 1 )

        if ( changeSomething ):
            # the order of the following calls counts ( maybe not anymore )
            line = self.storeRemoveOptionOutputDir( line )
            optionsList = [ '/nologo' ]
            index = self.findLastIndexInList( optionsList, line, True )
            if ( index == -1 ):
                raise Exception( 'ADD LIB32 line without any option between %s. Please improve the code or check the line.' % optionsList )
            line = self.addStoredOptions( line, index, optionsList )

        return line

    def changeOptionsBsc( self, line ):
        self.storedOptions = []

        changeSomething =   ( app.options.reformatOptionBrowse[self.c] == 1 )

        if ( changeSomething ):
            # the order of the following calls counts ( maybe not anymore )
            line = self.storeRemoveOptionBrowse( line )
            optionsList = [ '/nologo' ] # '# ADD BSC32' would give error: unbalanced parenthesis in the regexpr of findIndexCloseToOption()
            index = self.findLastIndexInList( optionsList, line, True )
            if ( index == -1 ):
                raise Exception( 'ADD BSC32 line without any option between %s. Please improve the code or check the line.' % optionsList )
            line = self.addStoredOptions( line, index, optionsList )

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

        #if ( self.addKind != enum_ADD_CPP ):
        #    if ( self.hasCustomBuildOutputDirList[self.nCfg] ):
        #        # nothing to do: already done in check
        #        self.checkCustomBuild( True )
        #        return line

        changeSomething = ( app.options.reformatOptionOutput[self.c] != 0 )
        if ( self.addKind == enum_ADD_CPP ):
            # (*) the reason why we always remove the '/Fo' option in a ADD CPP line is that vc6 always does it ( or at least when the value is the the same as Intermediate_Dir )
            addDir  = False
            addFile = False
            line = self.storeAndRemoveOption( line, '/Fo', self.PropIntermeDir, '', False, changeSomething, addDir, addFile )
        else:
            # this option should always be there ( we always want dir and filename specified for the linker output )
            addDir  = +1 # never remove it
            addFile = +1
            line = self.storeAndRemoveOption( line, '/out:', self.OutputDirOut, self.mainFileTitleBase + self.outputExt, False, changeSomething, addDir, addFile )

        if ( 0 < self.nCfg ):
            if ( not self.warning_done_dirs_different_between_cfgs ):
                self.warning_done_dirs_different_between_cfgs = True
                temp = self.OutputDirOut.lower().replace( self.configNameList[self.nCfg].lower(), self.configNameList[0].lower() )
                if ( temp != self.OutputDirOutList[0].lower() ):
                    print '  Warning!: the project \'%s\' has a LINK32 /out: directory \'%s\' for the config \'%s\' not corresponding with the directory \'%s\' for the config \'%s\'.' % ( os.path.basename(self.filename), self.OutputDirOutList[self.nCfg], self.configNameList[self.nCfg], self.OutputDirOutList[0], self.configNameList[0] )

        if ( self.appType == enumAppTypeExe ):
            if ( self.OutputDirOut != self.PropIntermeDir ):
                if ( self.filename.lower().find( g_subdir_examples ) != -1 ):
                    # automatically fixed because it is a very common mistake
                    print '  Warning!: the executable of %s has a LINK32 /out: directory different than the PROP_Output_Dir: \'%s\' != \'%s\'. This will be fixed.' % ( os.path.basename(self.filename), self.OutputDirOut, self.PropOutputDir )
                    self.OutputDirOut = self.PropOutputDir
                    self.OutputDirOutList[self.nCfg] = self.PropOutputDir
                else:
                    if ( 0 < app.options.warning ):
                        if ( not self.warning_done_dir_out_different_than_dir_prop and self.OutputDirOut == './' or self.OutputDirOut == '\\'  ):
                            self.warning_done_dir_out_different_than_dir_prop = True
                            print '  Warning!: the executable of %s has a LINK32 /out: directory different than the PROP_Output_Dir: \'%s\' != \'%s\'.' % ( os.path.basename(self.filename), self.OutputDirOut, self.PropOutputDir )

        return line

    def storeRemoveOptionOptimize( self, line ):
        changeSomething = ( app.options.reformatOptionOptimize[self.c] and app.options.reformatOptionOptimize[self.c] != '0' )
        if ( self.addKind == enum_ADD_CPP and changeSomething ):
            # we always add / replace something; never delete anything
            addDir  = changeSomething
            addFile = addDir # we usually want both in the same way
            option = '/' + app.options.reformatOptionOptimize[self.c]
            for opt in [ '/O1', '/O2', '/Od' ]:
                line = self.storeAndRemoveOption( line, opt, '', '', False, changeSomething, addDir, addFile, False )
            self.storedOptions.append( option )
        return line

    def storeRemoveOptionPdb( self, line ):
        # reformat a line for ProgramDatabase option ( /Fd /pdb: )
        changeSomething = ( app.options.reformatOptionPdb[self.c] != 0 )
        if ( changeSomething ):
            if ( self.addKind == enum_ADD_CPP ):
                # (*) the reason why we always remove the '/Fd' option in a ADD CPP line is that vc6 always does it ( or at least when the value is the the same as the output project aside the extension )
                if ( self.appType == enumAppTypeExe ):
                    addDir  = False
                    addFile = False # we usually want both in the same way
                    line = self.storeAndRemoveOption( line, '/Fd', self.OutputDirOut, '', False, changeSomething, addDir, addFile )
                else:
                    if ( self.appType == enumAppTypeLib or self.appType == enumAppTypeDll ):
                        addDir  = app.options.reformatOptionPdb[self.c]# remove it with -1 only
                        addFile = addDir# we usually want both in the same way
                    else:
                        addDir  = False # this will remove the option always
                        addFile = addDir# we usually want both in the same way
                    # for DLL's and Lib's also the filename is specified (and the link option '/pdb:' does not exist)
                    line = self.storeAndRemoveOption( line, '/Fd', self.OutputDirOut, self.mainFileTitleBase + '.pdb', False, changeSomething, addDir, addFile )
            elif ( self.addKind == enum_ADD_LINK32 or self.addKind == enum_ADD_LIB32 ):
                # (*) the reason why we always remove the '/pdb' option in a ADD LINK32 line is that vc6 always does it ( or at least when the value is the the same as the output project aside the extension )
                addDir  = False
                addFile = False # we usually want both in the same way
                line = self.storeAndRemoveOption( line, '/pdb:', self.OutputDirOut, self.mainFileTitleBase + '.pdb', False, changeSomething, addDir, addFile )

                if ( self.addKind == enum_ADD_LINK32 ):
                    addDir  = app.options.reformatOptionPdb[self.c]
                    addFile = addDir # we usually want both in the same way
                    line = self.storeAndRemoveOption( line, '/debug', '', '', False, changeSomething, addDir, addFile )

            elif ( self.addKind == enum_SUBTRACT_LINK32 ):
                # '/debug' in # SUBTRACT LINK32 disable the pdb option
                addDir  = -(app.options.reformatOptionPdb[self.c]) # /debug in the SUBTRACT line has opposite meaning
                addFile = addDir # we usually want both in the same way
                line = self.storeAndRemoveOption( line, '/debug', '', '', False, changeSomething, addDir, addFile )
        return line

    def storeRemoveOptionBrowse( self, line ):
        # reformat a line for Browse database option ( /FR /Fr /o: )
        changeSomething = ( app.options.reformatOptionBrowse[self.c] != 0 )
        addDir  = app.options.reformatOptionBrowse[self.c]
        addFile = addDir # we usually want both in the same way
        if ( self.addKind == enum_ADD_CPP ):
            line = self.storeAndRemoveOption( line, '/FR', self.PropIntermeDir, '', True, changeSomething, addDir, addFile )
        elif ( self.addKind == enum_ADD_LINK32 or self.addKind == enum_ADD_LIB32 ):
            # the bsc file will be placed in the same dir of the main output
            line = self.storeAndRemoveOption( line, '/o', self.OutputDirOut, self.mainFileTitleBase + '.bsc', False, changeSomething, addDir, addFile )
        elif ( self.addKind == enum_SUBTRACT_CPP ):
            # /Fr' in # SUBTRACT CPP disable the pdb option
            addDir  = -(app.options.reformatOptionBrowse[self.c]) # /debug in the SUBTRACT line has opposite meaning
            addFile = addDir # we usually want both in the same way
            line = self.storeAndRemoveOption( line, '/FR', '', '', True, changeSomething, addDir, addFile )
        return line

    def storeAndRemoveOption( self, line, option, directory, filename, ignorecase, changeSomething, addDir, addFile, store=True ):
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
                ( (ipf, basetitle, cpl), ( stat, dbg ) ) = DspFile.getPostFixIndex( fn )

                if ( ipf != -1 ):
                    fn = fn[:ipf]

                putPostfix = True
                if ( app.projectsNoPostfixList or app.projectsNoPostfixOutputList or app.projectsNoPostfixIfUnderCompilerDirList ):
                    if ( self.isInProjectsNoPostfixList() or self.isInProjectsNoPostfixOutputList() or self.isInProjectsNoPostfixIfUnderCompilerDirList() ):
                        putPostfix = False
                if ( putPostfix ):
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
            # (/Fd:"vc6\Debug\Very-Beautiful Actions_vc6.pdb") or /machine:i386 ( but no spaces )
            rec = re.compile( r'(?P<fulloption> %s(\s*?)"(?P<optionarg>[a-zA-Z0-9_\- $\(\)\\/.]*)") | (?P<fulloption2> %s(?P<optionarg2>[a-zA-Z0-9_\-$\(\)\\/.]*))' % (option,option), reOption )
        else:
            # (/Fd "vc6\Debug\Very-Beautiful Actions_vc6.pdb") or /FR ) ( isolated option with no argument )
            rec = re.compile( r'(?P<fulloption> %s(\s*?)"(?P<optionarg>[a-zA-Z0-9_\- $\(\)\\/.]*)") | (?P<optionalone> %s(\s+?))' % (option,option), reOption )

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

    def addStoredOptions( self, line, index, optionsList ):
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

    def moveOptionsProperOrder( self, line, optionsList ):
        # this function is the right one to always place the options in the order wanted by VisualStudio
        # it it is too complicated. Is there a better way ? But it works

        # create list
        p = line.find( '/' )
        if ( p == -1 ):
            # no options
            return line

        list = []
        s = line[:p]
        preOptions = s
        list.append( s )

        lineopt = line[p:]
        lineopt.rstrip() # eliminates last '\n'

        lista = []
        lista = lineopt.split( ' ' )
        lenlista = len ( lista )
        if ( not lenlista ):
            return line

        # the option are of this kind:
        # (/Fd:"vc6\Debug\Beautiful Actions_vc6.pdb") or /machine:i386 ( but no spaces )
        # (/Fd "vc6\Debug\Beautiful Actions_vc6.pdb") or /FR ) ( isolated option with no argument )

        opt = ''
        i = 0
        s = ''
        #listx = [] # for debug
        listOpt = []
        self.optionsDict = {}
        while ( i < lenlista ):
            item = lista[ i ].rstrip()
            i = i + 1
            if ( item and item[0] == '/' ):
                if ( s ):
                    s = s.strip()
                    #list.append( s )
                    #listx.append( s )
                    if ( self.optionsDict.has_key( opt ) ):
                        ss = self.optionsDict[opt]
                        self.optionsDict[opt] = ss + ' ' + s
                    else:
                        listOpt.append( opt )
                        self.optionsDict[opt] = s
                    s = ''

            if ( not s ):
                #first part of s
                it = item.strip()
                if ( it ):
                    c = it.find( ':' )
                    if ( c != -1 ):
                        opt = item[:c] + ':'
                    else:
                        c = it.find( '\"' )
                        if ( c != -1 ):
                            opt = item[:c] # + '\"' # no for \"
                        else:
                            opt = item

            s = s + ' ' + item
            pass
        if ( s ):
            s = s.strip()
            #list.append( s )
            #listx.append( s )
            if ( self.optionsDict.has_key( opt ) ):
                # if ( opt == '/libpath:' ): #the only option I can think of that can be repeated ...
                ss = self.optionsDict[opt]
                self.optionsDict[opt] = ss + ' ' + s
            else:
                listOpt.append( opt )
                self.optionsDict[opt] = s
            s = ''

        #for item in list:
        #    print '\'' + item + '\''
        #print self.optionsDict

        #between the two lists: listOpt and optionsList
        # we need to recreate listOpt but folowing the order in optionsList
        # to make it simple I put as many options as possible in the listOptions
        # first I add all the options that are not in listOptions
        # then I loop in listOptions and put them if they exist in listOpt
        # then all the remaining options in listOpt are put at the end

        doneDict = {}
        linex = ''
        n = 0
        found = False
        for opt in listOpt:
            for op in optionsList:
                if (op == opt):
                    found = True
                    break
            if ( found ):
                break
            else:
                linex = linex + ' ' + self.optionsDict[opt]
                doneDict[ opt ] = n
                n = n + 1

        for op in optionsList:
            if ( self.optionsDict.has_key( op ) ):
                linex = linex + ' ' + self.optionsDict[op]
                doneDict[ op ] = n
                n = n + 1

        for opt in listOpt:
            if ( not doneDict.has_key( opt ) ):
                linex = linex + ' ' + self.optionsDict[opt]

        #msg = 'Unknown option (%s). Please add it to the optionsList list [%s]. File \'%s\'. Line: \'%s\'' % ( opt, optionsList, self.filename, line.rstrip() )
        #app.logFilePrintLine( msg )

        newLine = preOptions + ' ' + linex + '\n'
        return newLine

        """
        # create line
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
        """
        return line

    def findIndexCloseToOption( self, line, option, ignorecase, before, repeat ):
        backward = False

        if ( ignorecase ):
            line   = line.lower()
            option = option.lower()

        # This accepts:
        # /D "BUILD_APPLICATIONKIT_LIB" /FR /Yu"ApplicationKit.h"
        # but also
        # /D "BUILD_APPLICATIONKIT_LIB" /FR"vc6\DebugDLL\" /Yu"ApplicationKit.h"
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



################################################################################
class SlnProjectData:
    """Structure to hold sln entries data fer each project in it"""
    def __init__( self ):
        self.reset()
        return

    def reset( self ):
        self.prjName = ''
        self.prjRelPath = ''
        self.prjAbsPath = ''
        self.prjUuid = ''

        self.prjConfigNameList     = []
        self.prjConfigFullNameList = []
        self.prjPlatformNameList   = []
        self.prjConfigOrPlatformNameList = []
        self.prjConfigFullNameExCfgPlatfAssocDict = {} #stupid format: GTK Debug.ActiveCfg = Debug|Win32

        self.prjDependenciesUuidList = []

        self.inspectedProject  = False  # tells if the info about the project have been taken by reading the projet itself
        self.inspectedSlnEntry = False # tells if the info about the project have been taken by reading the entry from a solution
        return

class Workspace( DspFile ):
    """Creates a workspace with all projects in Visual Studio 6."""
    def __init__( self, workspacename, checkExistence = True ):
        DspFile.__init__( self, workspacename )

        self.resetWorkspace()
        self.setName( workspacename, checkExistence )

    def __del__(self):
        #print "del Workspace"
        pass

    def resetWorkspace( self ):
        self.prjNames = []
        self.prjNamesLwr = []
        self.prjNamesDict = {}
        self.prjRelPaths = []
        self.prjAbsPaths = []
        self.prjNameAbsPathDict = {}
        self.prjNameRelPathDict = {}
        self.prjNameUuidDict = {}
        self.prjUuidNameDict = {} # reverse dictionary - but the value is not lowercase
        self.dictSlnProjectDataByName = {} # dictionary of all the SlnProjectData by Name
        self.dictSlnProjectDataByUuid = {} # usually more useful because this the way a sln works
        self.prjConfigFullNameList = [] # list of all configFullName existing between all the projects in a solution
        self.dswProjnameDependencyListDict = {} # dictionary of all the dependencies in a dsw workspace

        self.filename = ''
        self.dependencies = {}


        # solutions specific
        self.solutionLine = ''
        self.solutionVersion = ''
        self.uuidDPCodeReview = ''
        return

    def setName( self, workspacename, checkExistence = True ):
        self.filename = workspacename
        # makes sure it has the '.dsw. extension
        ( root, ext ) = os.path.splitext( self.filename )
        if ( ext == '' ):
            self.filename = root + '.dsw'

        workspaceDirname = os.path.dirname( workspacename )
        if ( checkExistence and not os.path.exists( workspaceDirname ) ):
            msg = 'The directory for the workspace \'%s\' does not exist. Create it [y/n] ? ' % workspacename
            c = raw_input( msg ).lower()
            if ( c == 'y' or c == 'yes' ):
                os.makedirs( workspaceDirname )
            else:
                raise Exception( 'Workspace\'s directory \'%s\' not created (by user request). Impossible to continue !' % workspaceDirname )
        return

    def addProject( self, prjName, absPrjPath ):
        # prjPath must be given here as absolute path because one thing is the path relative to the cwd
        # and different thing is aa path relative to the workspace path
        self.prjNames.append( prjName )
        prjNameLwr = prjName.lower() # changed 20040603
        self.prjNamesLwr.append( prjNameLwr )
        self.prjNamesDict[ prjNameLwr ] = prjName
        self.prjAbsPaths.append( absPrjPath )
        self.prjNameAbsPathDict[ prjNameLwr ] = absPrjPath

        workspaceDirname = os.path.dirname( self.filename )
        relPrjPath = FileUtils.relativePath( workspaceDirname, absPrjPath, True, g_internal_unixStyle )
        self.prjRelPaths.append( relPrjPath )
        self.prjNameRelPathDict[ prjNameLwr ] = relPrjPath

        return

    def duplicateVcs( self, updateOriginal ):
        # duplicates original workspace and/or reformat it in a canonic way
        if ( updateOriginal ):                # always %%% this *must* be *before* the others, so the dependencies are copied right
            self.duplicateVcDswSln( '' )  # this just reformat the original ( see duplicateVc ) - to use it with True or False is the same

        if ( app.options.copyToIcl7 ):
        #    #changeSolutions = False so it does not creates solutions
            self.duplicateVcDswSln( compilerIcl7, False )

        if ( app.options.copyToVc70 ):
            self.duplicateVcDswSln( compilerVc70 )

        if ( app.options.copyToVc71 ):
            self.duplicateVcDswSln( compilerVc71 )

    def duplicateVcDswSln( self, newCompiler, changeSolutions = True ):
        # duplicates workspaces from the current compiler (i.e. vc6) into the new compiler name ( _vc70 ) and subdirectory (vc70/)
        # just reformat the original if (newCompiler == '') ( i.e. make sure projectPath has the "" around of it )

        # with changeSolutions = False it works in the old way

        # if newCompiler == '' then the option changeSolutions is totally uneffective

        if ( app.options.enableVcfSpecific ):
            oldFilenameDsw = self.filename
            oldCompiler = compilerVc6

            updateSln = False
            newFilenameDsw = oldFilenameDsw
            if ( newCompiler ):
                newFilenameDsw = DspFile.makeDuplicateVcFilename( oldFilenameDsw, oldCompiler, newCompiler, g_internal_unixStyle, True )

                if ( changeSolutions ):
                    if ( app.options.synchVcprojSln ):
                        ( filename, ext ) = os.path.splitext( newFilenameDsw )
                        newFilenameSln = filename + extSln
                        newBasenameSln = os.path.basename( newFilenameSln )
                        if ( os.path.exists( newFilenameSln ) ):
                            updateSln = True
                            #else does a copy as dsw just as if ( not app.options.synchVcprojSln )

                        wspOld = self
                        sln = Workspace( oldFilenameDsw )
                        if ( updateSln ):
                            sln.conformSlnLikeDsw( wspOld, newFilenameSln, newCompiler )
                        else:
                            sln.createSlnFromDsw( wspOld, newFilenameSln, newCompiler )

                    if ( app.options.keepDspCopy ):
                        # the trick to copy and rename a file is to treat it as a DspFile as far as it concerns the functions here
                        wspOld = self
                        wsp = Workspace( oldFilenameDsw )
                        wsp.reformatDswSave( wspOld, newCompiler, newFilenameDsw )
                    else:
                        if ( os.path.exists( newFilenameDsw ) ):
                            os.remove( newFilenameDsw ) #%%% # wait before removing the solutions !
                            pass
                else:
                    wspOld = self
                    wsp = Workspace( oldFilenameDsw )
                    wsp.reformatDswSave( wspOld, newCompiler, newFilenameDsw )
            else:
                # the trick to copy and rename a file is to treat it as a DspFile as far as it concerns the functions here
                wspOld = self
                wsp = Workspace( oldFilenameDsw )
                wsp.reformatDswSave( wspOld, newCompiler, self.filename )

        return

    def reformatDswSave( self, wspOld, newCompiler, newFilename ):
        # the trick to copy and rename a file is to treat it as a DspFile as far as it concerns the functions here
        #wsp = DspFile( oldFilenameDsw )
        #wsp.setCompilerStrings( compilerVc6 )
        #( wsp.compiler, wsp.compilerUnderscor, wsp.compilerSep ) = DspFile.makeCompilerStrings( compilerVc6, g_internal_unixStyle )
        oldFilename = self.filename

        wspOld.readlines()

        wspOld.removeUnwantedLines()
        if ( self.isFileIn2() ):
            p = 1
        # this is not enough: we need to update the dependencies
        # the best is to re-create the workspace after collecting its data
        wspOld.getDswProjectEntries()
        wspOld.copyWorkspaceDependencies( app.options.dependenciesWorkspace )
        wspOld.createBuildLines( wspOld.prjNames, '', True ) # , wspOld.prjAbsPaths
        # wspOld.duplicateVcs( True ) # %%% was False, but why not to update and reformat the original ?

        Workspace.replaceProjectEntries( wspOld.lines, wspOld, newCompiler, oldFilename )

        # newPath = DspFile.makeDuplicateVcFilename( self.filename, dsp.compiler, newCompiler, g_internal_unixStyle, False )
        #if ( newCompiler ):
        #    newFilenameDsw = wsp.getDuplicateVcFilename( newCompiler, True )
        #    #return DspFile.makeDuplicateVcFilename( self.filename, self.compiler, newCompiler, g_internal_unixStyle, keepFirstDot )

        self.setFilename( newFilename )
        self.lines = wspOld.lines # copy all modified lines

        self.saveFile( g_include_vcproj_in_changed_files_counted, app.options.enableProjectFilesModif )

        if ( 0 < app.options.verbose ):
            if ( newCompiler ):
                print ' created workspace: %s' % self.filename
            else:
                print ' updated workspace: %s' % self.filename
        return

    def createSlnFromDsw( self, wspOld, newFilenameSln, newCompiler ):
        #creates a solution and fill it with projects according to the list of them in the corresponding workspace
        oldFilename = wspOld.filename

        wspOld.readlines()
        wspOld.getDswProjectEntries()

        wspOld.integrateSolutionEntriesInfos()
        if ( g_workspaceHasPrecedenceOverSolution or 0 == len( self.prjConfigFullNameList ) ):
            self.prjConfigFullNameList = wspOld.prjConfigFullNameList
        if ( 0 == len( self.prjConfigFullNameList ) ):
            raise Exception( 'createSlnFromDsw: self.prjConfigFullNameList is empty. File: \'%s\'' % ( self.filename ) )

        self.setFilename( newFilenameSln )

        self.createSlnProjectEntries( wspOld, newCompiler )

        self.setFilename( newFilenameSln  ) #%%% + '.sln'
        self.saveFile( g_include_vcproj_in_changed_files_counted, app.options.enableProjectFilesModif )

        if ( 0 < app.options.verbose ):
            print ' created solution: %s' % self.filename
        return

    def conformSlnLikeDsw( self, wspOld, newFilenameSln, newCompiler ):
        #add projects to an existing solution according to the list of them in the corresponding workspace
        oldFilename = wspOld.filename

        wspOld.readlines()
        wspOld.getDswProjectEntries()

        self.setFilename( newFilenameSln )
        if ( not os.path.exists( newFilenameSln ) ):
            raise Exception( 'The solution %s is expected to exist !' % newFilenameSln )

        self.readlines()
        self.getSlnProjectEntries( newCompiler )

        # make sure self.prjConfigFullNameList is getting data from the wspOld if it hasn't any yet
        if ( 0 == len( self.prjConfigFullNameList ) ):
            # integrate infos for the solution from the reference solution file if necessary
            if ( 0 == len( wspOld.prjConfigFullNameList ) ):
                wspOld.integrateSolutionEntriesInfos()
            if ( 0 == len( wspOld.prjConfigFullNameList ) ):
                raise Exception( 'conformSlnLikeDsw: self.prjConfigFullNameList is empty. File: \'%s\'' % ( self.filename ) )
            self.prjConfigFullNameList = wspOld.prjConfigFullNameList

        self.updateSlnProjectEntries( wspOld, newCompiler )

        self.setFilename( newFilenameSln ) #%%% + '.sln'
        self.saveFile( g_include_vcproj_in_changed_files_counted, app.options.enableProjectFilesModif )

        if ( 0 < app.options.verbose ):
            print ' updated solution: %s' % self.filename
        return

    def getDswProjectEntries( self ):
        # makes sure the project entries of a workspace are properly formatted
        # i.e. they must be inside commas and the relative path name written in normal/canonic way

        self.prjNames = []
        self.prjNamesLwr = []
        self.prjNamesDict = {}
        self.prjRelPaths = []
        self.prjAbsPaths = []
        self.prjNameRelPathDict = {}
        self.prjNameAbsPathDict = {}
        self.prjConfigNameList = []
        self.dswProjnameDependencyListDict = {}
        projnameDependencyList = []

        prjNameLwr = ''

        state = 0
        nPrjs = 0

        if ( FileUtils.isRelativePath( self.filename ) ):
            namedir = FileUtils.absolutePath( app.currentdir, self.filename, g_internal_unixStyle )
        else:
            namedir = self.filename
        namedir = os.path.dirname( namedir )
        namedir = FileUtils.normDir( namedir, g_internal_unixStyle, True )

        someDependencies = False

        for n in range( len( self.lines ) ):
            line = self.lines[n]
            self.n = n + 1

            m1 = reDswProjectEntryMin.match( line )
            if ( m1 ):
                m2 = reDswProjectEntryFull.match( line )
                if ( not m2 ):
                    raise Exception( 'Bad parsing in workspace %s - line %d: %s' % ( filename, n, line.rstrip() ) )
                prjName = m2.group('prjName')
                prjPath = m2.group('prjPath')
                # pkgOwnr = m2.group('pkgOwnr')
                prjNameLwr = prjName.lower()

                newline = r'Project: "' + prjName + r'"=' + prjPath + ' - Package Owner=<4>\n'
                if ( newline != line ):
                    print line; print newline
                    if ( newline.strip() == line.strip() ):
                        raise Exception( 'Wrong parsing in workspace %s - line[%d] [%s]  !=  newline[%s]\n [prjName = \'%s\', prjPath = \'%s\'\nBut they differ only by CR: are you using Cywing ? Please report to the author of the script.' % ( filename, n, line.rstrip(), newline, prjName, prjPath ) )
                    else:
                        raise Exception( 'Wrong parsing in workspace %s - line[%d] [%s]  !=  newline[%s]\n [prjName = \'%s\', prjPath = \'%s\'' % ( filename, n, line.rstrip(), newline, prjName, prjPath ) )

                prjPath = StringUtils.trimQuotes( prjPath )
                #if ( newCompiler ):
                #    newPath = DspFile.makeDuplicateVcFilename( prjPath, wsp.compiler, newCompiler, g_internal_unixStyle, True )
                #else:
                #    # we need to do this first otherwise problems under Cygwin when g_internal_unixStyle=True but the path starts with r'.\'
                #    newPath = FileUtils.normPathSimple( prjPath, g_internal_unixStyle )
                newPath = FileUtils.normPathSimple( prjPath, g_internal_unixStyle ) #app.options.unixStyle

                #newline = r'Project: "' + prjName + r'"="' + newPath + '" - Package Owner=<4>\n'

                self.prjRelPaths.append( newPath )
                prjAbsPath = FileUtils.absolutePath( namedir, newPath, g_internal_unixStyle )
                self.prjAbsPaths.append( prjAbsPath )

                #basename = os.path.basename( newPath )
                #basenameLwr = basename.lower()
                self.prjNames.append( prjName )
                prjNameLwr = prjName.lower()
                self.prjNamesLwr.append( prjNameLwr )
                self.prjNamesDict[ prjNameLwr ] = prjName
                self.prjNameRelPathDict[ prjNameLwr ] = newPath
                self.prjNameAbsPathDict[ prjNameLwr ] = prjAbsPath

                # this create at least an empty list for each project in the dictionary
                someDependencies = False
                projnameDependencyList = []
                self.dswProjnameDependencyListDict[ prjNameLwr ] = projnameDependencyList
                pass

            #    Begin Project Dependency
            #m_dsw_projectDependency_beg = re_dsw_projectDependency_beg.match( line )
            #if ( m_dsw_projectDependency_beg ):
            #    projnameDependencyList = []

            #    Project_Dep_Name ApplicationKitDLL
            m_dsw_projectDependency_entry = re_dsw_projectDependency_entry.match( line )
            if ( m_dsw_projectDependency_entry ):
                projnamedep = m_dsw_projectDependency_entry.group( 'projnamedep' )
                projnameDependencyList.append( projnamedep )
                someDependencies = True

            #    End Project Dependency
            #m_dsw_projectDependency_end = re_dsw_projectDependency_end.match( line )
            #if ( m_dsw_projectDependency_end ):
            m_dsw_package_end = re_dsw_package_end.match( line )
            if ( m_dsw_package_end ):
                if ( someDependencies ):
                    # not really necessary because projnameDependencyList in the dictionary is a reference !
                    self.dswProjnameDependencyListDict[ prjNameLwr ] = projnameDependencyList
                pass

            #self.lines[n] = newline

            pass
        return

    def getSlnProjectEntries( self, newCompiler ):
        # makes sure the project entries of a workspace are properly formatted
        # i.e. they must be inside commas and the relative path name written in normal/canonic way

        self.prjNames = []
        self.prjNamesLwr = []
        self.prjNamesDict = {}
        self.prjRelPaths = []
        self.prjAbsPaths = []
        self.prjNameRelPathDict = {}
        self.prjNameAbsPathDict = {}
        self.prjNameUuidDict = {}
        self.prjUuidNameDict = {} # reverse dictionary - but the value is not lowercase

        self.solutionLine = ''
        self.solutionVersion = ''


        state = 0
        sectionState = enumSection_None
        nPrjs = 0
        foundGlobalSectionDPCodeReviewSolutionGUID = False
        foundGlobalSectionSolutionConfiguration = False
        foundGlobalSectionProjectDependencies = False
        foundGlobalSectionProjectConfiguration = False
        foundGlobalSectionExtensibilityGlobals = False
        foundGlobalSectionExtensibilityAddIns = False

        prjName = ''
        prjNameLwr = ''

        prjConfigNameList     = []
        prjConfigFullNameList = []
        prjPlatformNameList   = []
        prjConfigOrPlatformNameList = []
        projectsWithConfigFullNameExCfgPlatfAssocDictDict = {}

        prjDependenciesUuidList = []
        depNum = -1
        depNumCheck = -1

        lastUuid = '-1'

        if ( FileUtils.isRelativePath( self.filename ) ):
            namedir = FileUtils.absolutePath( app.currentdir, self.filename, g_internal_unixStyle )
        else:
            namedir = self.filename
        namedir = os.path.dirname( namedir )
        namedir = FileUtils.normDir( namedir, g_internal_unixStyle, True )

        for n in range( len( self.lines ) ):
            line = self.lines[n]
            self.n = n + 1

            if ( state == 0 ):
                version = ''
                m_sln_solutionFileVersion = re_sln_solutionFileVersion.match( line )
                if ( m_sln_solutionFileVersion ):
                    version = m_sln_solutionFileVersion.group( 'slnVersion' )
                if ( version == '7.00' ):
                    if ( newCompiler != compilerVc70 ):
                        raise Exception( 'getSlnProjectEntries: incompatible solution version [%s] found for the compiler \'%s\' in line [%d] file %s' % ( version, newCompiler, self.n, self.filename ) )
                elif ( version == '8.00' ):
                    if ( newCompiler != compilerVc71 ):
                        raise Exception( 'getSlnProjectEntries: incompatible solution version [%s] found for the compiler \'%s\' in line [%d] file %s' % ( version, newCompiler, self.n, self.filename ) )
                else:
                    raise Exception( 'getSlnProjectEntries: unknown solution version [%s] found for the compiler \'%s\' in line [%d] file %s' % ( version, newCompiler, self.n, self.filename ) )

                self.solutionVersion = version
                self.solutionLine = line.rstrip()
                state = 1

            elif ( state == 1 ):
                #Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "AdvancedAlignment", "..\..\examples\AdvancedAlignment\AdvancedAlignment_vc70.vcproj", "{6C719125-E179-496A-8F9E-B3F34748FE15}"
                m_sln_projectpath_entry = re_sln_projectpath_entry.match( line )
                if ( m_sln_projectpath_entry ):
                    uuidVs   = m_sln_projectpath_entry.group( 'uuidVs' )
                    prjName = m_sln_projectpath_entry.group( 'projname' )
                    prjPath = m_sln_projectpath_entry.group( 'projPath' )
                    uuidProj = m_sln_projectpath_entry.group( 'uuidProj' )
                    if ( uuidVs != g_uuidVisualStudio ): # '8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942'
                        #raise Exception( 'getSlnProjectEntries: incompatible uuid for VisualStudio. Script changed ? {%s} != {%s}. File \'%s\'. Line [%d] \'%s\'' % ( uuidVs, g_uuidVisualStudio, self.filename, self.n, line.rstrip() ) )
                        print Exception( 'getSlnProjectEntries: incompatible uuid for VisualStudio. Script changed ? Fixed anyway {%s} != {%s}. File \'%s\'. Line [%d] \'%s\'' % ( uuidVs, g_uuidVisualStudio, self.filename, self.n, line.rstrip() ) )
                    if ( len( uuidProj ) != 36 ):
                        raise Exception( 'getSlnProjectEntries: wrong uuid extracted: less than 36 chars {%s}. File \'%s\'. Line [%d] \'%s\'' % ( uuidProj, self.filename, self.n, line.rstrip() ) )

                    newPath = FileUtils.normPathSimple( prjPath, g_internal_unixStyle ) #not app.options.unixStyle
                    self.prjRelPaths.append( newPath )
                    prjAbsPath = FileUtils.absolutePath( namedir, newPath, g_internal_unixStyle )
                    self.prjAbsPaths.append( prjAbsPath )
                    #basename = os.path.basename( newPath )
                    #basenameLwr = basename.lower()
                    prjNameLwr = prjName.lower()

                    if ( app.allUsedUuidsDict.has_key( uuidProj ) and app.allUsedUuidsDict[ uuidProj ] == prjName.lower() ):
                        pass
                    else:
                        if ( app.allUsedUuidsDict.has_key( uuidProj ) ):
                            msg = 'getSlnProjectEntries: this uuid {%s} for [%s] has been already used for another project [%s]. This will be fixed!. File \'%s\'. Line [%d] \'%s\'' % ( uuidProj, prjName, app.allUsedUuidsDict[ uuidProj ], self.filename, self.n, line.rstrip() )
                            #raise Exception( msg )
                            print msg
                            uuidProj = app.getNextUuid( prjName )
                            print 'Using key: {%s}' % ( uuidProj )
                        else:
                            app.addUuid( uuidProj, prjName )

                    self.prjNames.append( prjName ) #added 200405
                    self.prjNamesLwr.append( prjNameLwr ) #added 200405
                    self.prjNamesDict[ prjNameLwr ] = prjName
                    self.prjNameRelPathDict[ prjNameLwr ] = prjPath
                    self.prjNameAbsPathDict[ prjNameLwr ] = prjAbsPath
                    self.prjNameUuidDict[ prjNameLwr ] = uuidProj
                    self.prjUuidNameDict[ uuidProj ] = prjName

                    slnPrjData = SlnProjectData()
                    slnPrjData.prjRelPath = prjPath
                    slnPrjData.prjAbsPath = prjAbsPath
                    slnPrjData.prjName = prjName
                    slnPrjData.prjUuid = uuidProj

                #       ProjectSection(ProjectDependencies) = postProject
                m_sln_projSectionDependency_beg = re_sln_projSectionDependency_beg.match( line )
                if ( m_sln_projSectionDependency_beg ):
                    prjDependenciesUuidList = []
                    continue

                #               {1BF58525-7F60-4646-94AD-2D41B97C5FD6} = {1BF58525-7F60-4646-94AD-2D41B97C5FD6}
                m_sln_dependency_entry = re_sln_dependency_entry.match( line )
                if ( m_sln_dependency_entry ):
                    if ( newCompiler == compilerVc71 ):
                        uuidProj = m_sln_dependency_entry.group( 'uuidProj' )
                        uuidProj2 = m_sln_dependency_entry.group( 'uuidProj2' )
                        if ( uuidProj != uuidProj2 ):
                            raise Exception( 'getSlnProjectEntries: ProjectSection(ProjectDependencies) with different uuids: {%s} != {%s}. File \'%s\'. Line \'%s\'' % ( uuidProj, uuidProj2, self.filename, line.rstrip() ) )
                        #dependProj = self.prjUuidNameDict[ uuidProj ] # not known yet for all the projects
                        prjDependenciesUuidList.append( uuidProj )
                        #self.prjUuidDependencyListDict[ uuidProj ] = uuidProj
                        continue
                    else:
                        raise Exception( 'getSlnProjectEntries: Here we shouldn\'t have found ProjectSection(ProjectDependencies): Microsoft Solution file v.%s  File \'%s\'. Line \'%s\'' % ( self.solutionVersion, self.filename, line.rstrip() ) )

                #EndProject
                m_sln_project_end = re_sln_project_end.match( line )
                if ( m_sln_project_end ):
                    slnPrjData.prjDependenciesUuidList = prjDependenciesUuidList # here not empty list only with compilerVc71
                    slnPrjData.inspectedSlnEntry = True
                    if ( slnPrjData.prjName != prjName ):
                        msg = 'getSlnProjectEntries: ERROR: [ %s != %s ] slnPrjData.prjName != prjName !. File: \'%s\'' % ( slnPrjData.prjName, prjName, self.filename )
                        raise Exception( msg )
                    self.dictSlnProjectDataByName[ prjNameLwr ] = slnPrjData
                    self.dictSlnProjectDataByUuid[ slnPrjData.prjUuid ] = slnPrjData
                    continue

                #Global
                m_sln_globals_beg = re_sln_globals_beg.match( line )
                if ( m_sln_globals_beg ):
                    #here we have at least all the projects already known as existing in the solution
##                    if ( newCompiler == compilerVc70 ):
##                        state = 2
##                    else:
##                        state = 3
                    state = 2

            elif ( state == 2 ):
                m_sln_globalSection_beg = re_sln_globalSection_beg.match( line )
                if ( m_sln_globalSection_beg ):
                    sectionName = m_sln_globalSection_beg.group( 'sectionName' );
                    #print sectionName

                    if ( sectionName == 'DPCodeReviewSolutionGUID' ):
                        sectionState = enumSection_DPCodeReviewSolutionGUID
                    elif ( sectionName == 'SolutionConfiguration' ):
                        sectionState = enumSection_SolutionConfiguration
                    elif ( sectionName == 'ProjectDependencies' ):
                        sectionState = enumSection_ProjectDependencies
                    elif ( sectionName == 'ProjectConfiguration' ):
                        sectionState = enumSection_ProjectConfiguration
                    elif ( sectionName == 'ExtensibilityGlobals' ):
                        sectionState = enumSection_ExtensibilityGlobals
                    elif ( sectionName == 'ExtensibilityAddIns' ):
                        sectionState = enumSection_ExtensibilityAddIns
                    else:
                        raise Exception( 'getSlnProjectEntries: unknown section name: GlobalSection(%s).  File \'%s\' (%d). Line \'%s\'' % ( self.solutionVersion, self.filename, self.n, line.rstrip() ) )
                else:
                    m_sln_globals_end = re_sln_globals_end.match( line )
                    if ( m_sln_globals_end ):
                        sectionState = enumSection_completed
                    # no exception: there are all the other lines !
                    #else:
                    #    raise Exception( 'getSlnProjectEntries: unable to parse the current line.  File \'%s\' (%d). Line \'%s\'' % ( self.filename, self.n, line.rstrip() ) )



                if ( False ):
                    pass

                elif ( sectionState == enumSection_DPCodeReviewSolutionGUID ):
                    if ( newCompiler == compilerVc70 ):
                        #   GlobalSection(DPCodeReviewSolutionGUID) = preSolution
                        m_sln_globalSectionDPCodeReview_beg = re_sln_globalSectionDPCodeReview_beg.match( line )
                        if ( m_sln_globalSectionDPCodeReview_beg ):
                            foundGlobalSectionDPCodeReviewSolutionGUID = True
                            continue

                        #           DPCodeReviewSolutionGUID = {00000000-0000-0000-0000-000000000000}
                        m_sln_globalSectionDPCodeReview_entry = re_sln_globalSectionDPCodeReview_entry.match( line )
                        if ( m_sln_globalSectionDPCodeReview_entry ):
                            uuidDPCodeReview = m_sln_globalSectionDPCodeReview_entry.group( 'uuidDPCodeReview' )
                            self.uuidDPCodeReview = uuidDPCodeReview
                            continue

                        #   EndGlobalSection
                        m_sln_globalSection_end = re_sln_globalSection_end.match( line )
                        if ( m_sln_globalSection_end ):
                            if ( not foundGlobalSectionDPCodeReviewSolutionGUID ):
                                raise Exception( 'getSlnProjectEntries: Here we shouldn\'t have found GlobalSection(DPCodeReviewSolutionGUID): Microsoft Solution file v.%s  File \'%s\' (%d). Line \'%s\'' % ( self.solutionVersion, self.filename, self.n, line.rstrip() ) )
##                            state = 3
                    else:
                        raise Exception( 'getSlnProjectEntries: We shouldn\'t be here: GlobalSection(DPCodeReviewSolutionGUID) does not exists with the version 8.00: Microsoft Solution file v.%s  File \'%s\' (%d). Line \'%s\'' % ( self.solutionVersion, self.filename, self.n, line.rstrip() ) )

                elif ( sectionState == enumSection_SolutionConfiguration ):
                #elif ( state == 3 ):
                    #       GlobalSection(SolutionConfiguration) = preSolution
                    m_sln_globalSectionSolConfig_beg = re_sln_globalSectionSolConfig_beg.match( line )
                    if ( m_sln_globalSectionSolConfig_beg ):
                        foundGlobalSectionSolutionConfiguration = True
                        continue

                    #               ConfigName.1 = GTK Debug     # with vc70
                    m_sln_globalSectionSolConfig_entryVc70 = re_sln_globalSectionSolConfig_entryVc70.match( line )
                    if ( m_sln_globalSectionSolConfig_entryVc70 ):
                        configNum = m_sln_globalSectionSolConfig_entryVc70.group( 'configNum' )
                        configName = m_sln_globalSectionSolConfig_entryVc70.group( 'configName' )
                        self.prjConfigFullNameList.append( configName ) # list of all configFullName existing between all the projects in a solution
                        continue

                    #               GTK Debug = GTK Debug        # with vc71
                    m_sln_globalSectionSolConfig_entryVc71 = re_sln_globalSectionSolConfig_entryVc71.match( line )
                    if ( m_sln_globalSectionSolConfig_entryVc71 ):
                        configName = m_sln_globalSectionSolConfig_entryVc71.group( 'configName' )
                        configName2 = m_sln_globalSectionSolConfig_entryVc71.group( 'configName2' )
                        if ( configName != configName2 ):
                            raise Exception( 'getSlnProjectEntries: ProjectSection(ProjectDependencies) with different configs: \'%s\' != \'%s\'. File \'%s\'. Line \'%s\'' % ( configName, configName2, self.filename, line.rstrip() ) )
                        self.prjConfigFullNameList.append( configName ) # # list of all configFullName existing between all the projects in a solution
                        continue

                    #       EndGlobalSection
                    m_sln_globalSection_end = re_sln_globalSection_end.match( line )
                    if ( m_sln_globalSection_end ):
                        if ( not foundGlobalSectionSolutionConfiguration ):
                            raise Exception( 'getSlnProjectEntries: Here we shouldn\'t have found GlobalSection(SolutionConfiguration): Microsoft Solution file v.%s  File \'%s\'. Line \'%s\'' % ( self.solutionVersion, self.filename, line.rstrip() ) )
##                        if ( newCompiler == compilerVc70 ):
##                            state = 4
##                        else:
##                            state = 5

                elif ( sectionState == enumSection_ProjectDependencies ):
                #elif ( state == 4 ):
                    if ( newCompiler == compilerVc70 ):
                        #   GlobalSection(ProjectDependencies) = postSolution
                        m_sln_globalSectionDependency_beg = re_sln_globalSectionDependency_beg.match( line )
                        if ( m_sln_globalSectionDependency_beg ):
                            foundGlobalSectionProjectDependencies = True
                            prjDependenciesUuidList = []
                            depNum = -1
                            depNumCheck = -1
                            lastUuid = '-1'
                            continue

                        #           {CFD6EAE2-10C6-466D-8BDE-A7E905B842C2}.0 = {AB72FB3C-CF7D-4FB4-B808-BF12C26E8B04}
                        m_sln_globalSectionDependency_entry = re_sln_globalSectionDependency_entry.match( line )
                        if ( m_sln_globalSectionDependency_entry ):
                            uuidProj  = m_sln_globalSectionDependency_entry.group( 'uuidProj'  )
                            uuidProj2 = m_sln_globalSectionDependency_entry.group( 'uuidProj2' )
                            depNumStr = m_sln_globalSectionDependency_entry.group( 'depNum' )
                            depNum = eval( depNumStr )

                            if ( lastUuid != '-1' and lastUuid != uuidProj ):
                                if ( depNumCheck != -1 ):
                                    if ( depNumCheck+1 != len(prjDependenciesUuidList) ):
                                        raise Exception( 'getSlnProjectEntries: depNumCheck+1 [=%d] != len(prjDependenciesUuidList) [=%d].   File \'%s\'. Line \'%s\'' % ( depNumCheck+1, len(prjDependenciesUuidList), self.filename, line.rstrip() ) )

                                    slnPrjData = self.dictSlnProjectDataByUuid[ lastUuid ]
                                    if ( not lastUuid == slnPrjData.prjUuid ):
                                        raise Exception( 'ERROR with: self.dictSlnProjectDataByUuid: uuidProj != self.dictSlnProjectDataByUuid[ uuidProj ].prjUuid: %s != %s' % ( lastUuid, self.dictSlnProjectDataByUuid[ lastUuid ].prjUuid ) )
                                    if ( 0 != len( slnPrjData.prjDependenciesUuidList ) ):
                                        raise Exception( 'ERROR: slnPrjData.prjDependenciesUuidList should be empty' )
                                    slnPrjData.prjDependenciesUuidList = prjDependenciesUuidList
                                    #self.dictSlnProjectDataByName[ nameLwr ]  = slnPrjData # not necessary because slnPrjData is a reference !
                                    #self.dictSlnProjectDataByUuid[ lastUuid ] = slnPrjData # not necessary because slnPrjData is a reference !
                                    prjDependenciesUuidList = []
                                    depNum = -1
                                    depNumCheck = -1
                                    lastUuid = '-1'

                            # %%% should we put this if so it doesn't chrash ?
                            # for sure we want to be able to remove some projcts from a solution if we want !
                            if ( self.dictSlnProjectDataByUuid.has_key( uuidProj2 ) ):
                                prjName1 = self.dictSlnProjectDataByUuid[ uuidProj  ].prjName # for debug
                                prjName2 = self.dictSlnProjectDataByUuid[ uuidProj2 ].prjName # for debug

                            depNumCheck = depNumCheck + 1
                            prjDependenciesUuidList.append( uuidProj2 )
                            lastUuid = uuidProj

                            continue

                        #   EndGlobalSection
                        m_sln_globalSection_end = re_sln_globalSection_end.match( line )
                        if ( m_sln_globalSection_end ):
                            if ( not foundGlobalSectionProjectDependencies ):
                                raise Exception( 'getSlnProjectEntries: Here we shouldn\'t have found GlobalSection(ProjectDependencies): Microsoft Solution file v.%s  File \'%s\'. Line \'%s\'' % ( self.solutionVersion, self.filename, line.rstrip() ) )

                            if ( depNumCheck != -1 ):
                                if ( depNumCheck+1 != len(prjDependenciesUuidList) ):
                                    raise Exception( 'getSlnProjectEntries: depNumCheck+1 [=%d] != len(prjDependenciesUuidList) [=%d].   File \'%s\'. Line \'%s\'' % ( depNumCheck+1, len(prjDependenciesUuidList), self.filename, line.rstrip() ) )

                                slnPrjData = self.dictSlnProjectDataByUuid[ lastUuid ]
                                if ( not lastUuid == slnPrjData.prjUuid ):
                                    raise Exception( 'ERROR with: self.dictSlnProjectDataByUuid: uuidProj != self.dictSlnProjectDataByUuid[ uuidProj ].prjUuid: %s != %s' % ( lastUuid, self.dictSlnProjectDataByUuid[ lastUuid ].prjUuid ) )
                                if ( 0 != len( slnPrjData.prjDependenciesUuidList ) ):
                                    raise Exception( 'ERROR: slnPrjData.prjDependenciesUuidList should be empty' )
                                slnPrjData.prjDependenciesUuidList = prjDependenciesUuidList
                                #self.dictSlnProjectDataByName[ nameLwr ]  = slnPrjData # not necessary because slnPrjData is a reference !
                                #self.dictSlnProjectDataByUuid[ lastUuid ] = slnPrjData # not necessary because slnPrjData is a reference !
                                prjDependenciesUuidList = []
                                depNum = -1
                                depNumCheck = -1
                                lastUuid = '-1'

##                            state = 5
                    else:
                        raise Exception( 'getSlnProjectEntries: We shouldn\'t be here: GlobalSection(ProjectDependencies) does not exists with the version  8.00: Microsoft Solution file v.%s  File \'%s\'. Line \'%s\'' % ( self.solutionVersion, self.filename, line.rstrip() ) )

                elif ( sectionState == enumSection_ProjectConfiguration ):
                #elif ( state == 5 ):
                    #       GlobalSection(ProjectConfiguration) = postSolution
                    m_sln_globalSectionProjectConfig_beg = re_sln_globalSectionProjectConfig_beg.match( line )
                    if ( m_sln_globalSectionProjectConfig_beg ):
                        foundGlobalSectionProjectConfiguration = True
                        prjConfigNameList     = []
                        prjConfigFullNameList = []
                        prjPlatformNameList   = []
                        prjConfigOrPlatformNameList = []
                        prjConfigFullNameExCfgPlatfAssocDict = {}
                        lastUuid = '-1'
                        continue

                    #               {7F3664CE-7A4D-4AC1-BB37-B2CD8404813E}.Debug.ActiveCfg = Debug|Win32
                    m_sln_globalSectionProjectConfig_entry = re_sln_globalSectionProjectConfig_entry.match( line )
                    if ( m_sln_globalSectionProjectConfig_entry ):
                        uuidProj = m_sln_globalSectionProjectConfig_entry.group( 'uuidProj' )

                        if ( lastUuid != '-1' and lastUuid != uuidProj ):
                            slnPrjData = self.dictSlnProjectDataByUuid[ lastUuid ]
                            if ( not lastUuid == slnPrjData.prjUuid ):
                                raise Exception( 'ERROR with self.dictSlnProjectDataByUuid: uuidProj != self.dictSlnProjectDataByUuid[ uuidProj ].prjUuid: %s != %s' % ( lastUuid, self.dictSlnProjectDataByUuid[ lastUuid ].prjUuid ) )
                            slnPrjData.prjConfigNameList     = prjConfigNameList
                            slnPrjData.prjConfigFullNameList = prjConfigFullNameList
                            slnPrjData.prjPlatformNameList   = prjPlatformNameList
                            slnPrjData.prjConfigOrPlatformNameList = prjConfigOrPlatformNameList
                            slnPrjData.prjConfigFullNameExCfgPlatfAssocDict = prjConfigFullNameExCfgPlatfAssocDict
                            #self.dictSlnProjectDataByName[ nameLwr ]  = slnPrjData # not necessary because slnPrjData is a reference !
                            #self.dictSlnProjectDataByUuid[ lastUuid ] = slnPrjData # not necessary because slnPrjData is a reference !
                            prjConfigNameList     = []
                            prjConfigFullNameList = []
                            prjPlatformNameList   = []
                            prjConfigOrPlatformNameList = []
                            prjConfigFullNameExCfgPlatfAssocDict = {}
                            lastUuid = '-1'


                        configNameExtended = m_sln_globalSectionProjectConfig_entry.group( 'configNameExtended' ) # configNameExtended = 'Debug.ActiveCfg'
                        configFullName = m_sln_globalSectionProjectConfig_entry.group( 'configFullName' )
                        platform = m_sln_globalSectionProjectConfig_entry.group( 'platform' )
                        configSplit = configFullName.split( ' ' )
                        config = configSplit[-1] # 'GTK Debug' --> 'Debug'
                        configOrPlatform = '%s|%s' % ( configFullName, platform )

                        #stupid format: GTK Debug.ActiveCfg = Debug|Win32
                        configFullNameEx = configNameExtended.split( '.' )[0]
                        prjConfigFullNameExCfgPlatfAssocDict[ configFullNameEx ] = configOrPlatform

                        slnPrjData = self.dictSlnProjectDataByUuid[ uuidProj ]
                        projectsWithConfigFullNameExCfgPlatfAssocDictDict[ slnPrjData.prjName.lower() ] = uuidProj

                        if ( StringUtils.findInList( configOrPlatform, prjConfigOrPlatformNameList ) == -1 ):
                            prjConfigOrPlatformNameList.append( configOrPlatform )
                            if ( StringUtils.findInList( config, prjConfigNameList ) == -1 ):
                                prjConfigNameList.append( config )
                            if ( StringUtils.findInList( configFullName, prjConfigFullNameList ) == -1 ):
                                prjConfigFullNameList.append( configFullName )
                            if ( StringUtils.findInList( platform, prjPlatformNameList ) == -1 ):
                                prjPlatformNameList.append( platform )
                        lastUuid = uuidProj
                        continue

                    #       EndGlobalSection
                    m_sln_globalSection_end = re_sln_globalSection_end.match( line )
                    if ( m_sln_globalSection_end ):
                        if ( not foundGlobalSectionProjectConfiguration ):
                            raise Exception( 'getSlnProjectEntries: Here we shouldn\'t have found GlobalSection(ProjectConfiguration): Microsoft Solution file v.%s  File \'%s\'. Line \'%s\'' % ( self.solutionVersion, self.filename, line.rstrip() ) )

                        slnPrjData = self.dictSlnProjectDataByUuid[ lastUuid ]
                        if ( not lastUuid == slnPrjData.prjUuid ):
                            raise Exception( 'ERROR with self.dictSlnProjectDataByUuid: uuidProj != self.dictSlnProjectDataByUuid[ uuidProj ].prjUuid: %s != %s' % ( lastUuid, self.dictSlnProjectDataByUuid[ lastUuid ].prjUuid ) )
                        slnPrjData.prjConfigNameList     = prjConfigNameList
                        slnPrjData.prjConfigFullNameList = prjConfigFullNameList
                        slnPrjData.prjPlatformNameList   = prjPlatformNameList
                        slnPrjData.prjConfigOrPlatformNameList = prjConfigOrPlatformNameList
                        slnPrjData.prjConfigFullNameExCfgPlatfAssocDict = prjConfigFullNameExCfgPlatfAssocDict
                        #self.dictSlnProjectDataByName[ nameLwr ]  = slnPrjData # not necessary because slnPrjData is a reference !
                        #self.dictSlnProjectDataByUuid[ lastUuid ] = slnPrjData # not necessary because slnPrjData is a reference !
                        prjConfigNameList     = []
                        prjConfigFullNameList = []
                        prjPlatformNameList   = []
                        prjConfigOrPlatformNameList = []
                        prjConfigFullNameExCfgPlatfAssocDict = {}
                        lastUuid = '-1'

##                        state = 6

                elif ( sectionState == enumSection_ExtensibilityGlobals ):
                #elif ( state == 6 ):
                    #       GlobalSection(ExtensibilityGlobals) = postSolution
                    m_sln_globalSectionExtensibGlobals_beg = re_sln_globalSectionExtensibGlobals_beg.match( line )
                    if ( m_sln_globalSectionExtensibGlobals_beg ):
                        foundGlobalSectionExtensibilityGlobals = True
                        continue

                    #       EndGlobalSection
                    m_sln_globalSection_end = re_sln_globalSection_end.match( line )
                    if ( m_sln_globalSection_end ):
                        if ( not foundGlobalSectionExtensibilityGlobals ):
                            raise Exception( 'getSlnProjectEntries: Here we shouldn\'t have found GlobalSection(ExtensibilityGlobals): Microsoft Solution file v.%s  File \'%s\'. Line \'%s\'' % ( self.solutionVersion, self.filename, line.rstrip() ) )
##                        state = 7

                elif ( sectionState == enumSection_ExtensibilityAddIns ):
                #elif ( state == 7 ):
                    #       GlobalSection(ExtensibilityAddIns) = postSolution
                    m_sln_globalSectionExtensibAddIns_beg = re_sln_globalSectionExtensibAddIns_beg.match( line )
                    if ( m_sln_globalSectionExtensibAddIns_beg ):
                        foundGlobalSectionExtensibilityAddIns = True
                        continue

                    #       EndGlobalSection
                    m_sln_globalSection_end = re_sln_globalSection_end.match( line )
                    if ( m_sln_globalSection_end ):
                        if ( not foundGlobalSectionExtensibilityAddIns ):
                            raise Exception( 'getSlnProjectEntries: Here we shouldn\'t have found GlobalSection(ExtensibilityAddIns): Microsoft Solution file v.%s  File \'%s\'. Line \'%s\'' % ( self.solutionVersion, self.filename, line.rstrip() ) )
##                        state = 8

                elif ( sectionState == enumSection_completed ):
                    state = 3

                else:
                    raise Exception( 'getSlnProjectEntries: wrong final sectionState: [%d]. Read %d lines in \'%s\'' % ( sectionState, self.n, self.filename ) )


            #self.lines[n] = newline

        if ( state != 3 ):
            raise Exception( 'getSlnProjectEntries: wrong final state: [%d]. Read %d lines in \'%s\'' % ( state, self.n, self.filename ) )

        # make sure we don't have a project with no configurations !
        # later we will need of: self.dictSlnProjectDataByName[ prjNameLwr ].prjConfigFullNameExCfgPlatfAssocDict
        for prjName in self.prjNames:
            prjNameLwr = prjName.lower()
            if ( not projectsWithConfigFullNameExCfgPlatfAssocDictDict.has_key( prjNameLwr ) ):
                msg = 'getSlnProjectEntries: ERROR: the project \'%s\' in the current solution does not exists in the section \'GlobalSection(ProjectConfiguration)\'. This will be fixed anyway. Read %d lines in \'%s\'' % ( prjName, self.n, self.filename )
                print msg
                #raise Exception( msg )
                slnPrjData = self.dictSlnProjectDataByName[ prjNameLwr ]

                if ( not referenceSolution.dictSlnProjectDataByUuid.has_key( slnPrjData.prjUuid ) ):
                    msg = 'IMPORTANT: if the script stops here it is necessary to manually remove the project [%s] from the solution and re-add it again !\n' % ( prjName )
                    msg = msg + ' or manually make sure the uuid inside the solution are uniquely used by each project.'
                    print msg
                    raise Exception( msg )

                if ( referenceSolution.dictSlnProjectDataByName[ prjNameLwr ].prjName != referenceSolution.dictSlnProjectDataByUuid[ slnPrjData.prjUuid ].prjName ):
                    msg = 'getSlnProjectEntries: ERROR: [ %s != %s ] referenceSolution.dictSlnProjectDataByName[ prjNameLwr ].prjName != referenceSolution.dictSlnProjectDataByUuid[ slnPrjData.prjUuid ].prjName !. File: \'%s\'' % ( referenceSolution.dictSlnProjectDataByName[ prjNameLwr ].prjName, referenceSolution.dictSlnProjectDataByUuid[ slnPrjData.prjUuid ].prjName, self.filename )
                    raise Exception( msg )
                prjAbsPath = self.prjNameAbsPathDict[ prjNameLwr ]
                # False: better to try with the dsp file otherwise the script will later complain for ( prjAbsPath != prjAbsPath2 )
                if ( app.allProjectNamesLwrPathsDict.has_key( prjNameLwr ) ):
                    # this avoid getProjectData() to complain
                    prjAbsPath = app.allProjectNamesLwrPathsDict[ prjNameLwr ]
                slnPrjData = self.getProjectData( prjName, prjAbsPath, None, False, slnPrjData.prjUuid )
                slnPrjData.inspectedProject = True
                if ( slnPrjData.prjName != prjName ):
                    msg = 'getSlnProjectEntries: ERROR: [ %s != %s ] slnPrjData.prjName != prjName !. File: \'%s\'' % ( slnPrjData.prjName, prjName, self.filename )
                    raise Exception( msg )
                referenceSolution.dictSlnProjectDataByName[ prjNameLwr ] = slnPrjData
                referenceSolution.dictSlnProjectDataByUuid[ slnPrjData.prjUuid ] = slnPrjData
        return

    def integrateSolutionEntriesInfos( self ):
        # in a workspace we miss many (useless) infos we have in a solution
        # in order to have them we need to 'integrate' those infos from the referenceSolution file

        configFullNameList = []

        for prjName in self.prjNames:
            #Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "Actions", "..\..\examples\Actions\Actions_vc70.vcproj", "{7F3664CE-7A4D-4AC1-BB37-B2CD8404813E}"
            #prjNameLwr = prjName.lower()
            # tries to get the uuid from the referenceSolution before creating a new uuid
            #( prjPath, prjUuid ) = self.getSlnProjectInfos( prjName, wspOld )
            slnPrjData = self.getSlnProjectData( prjName, '', None )
            prjAbsPath = slnPrjData.prjAbsPath
            #
            prjUuid = slnPrjData.prjUuid

            for configFullName in slnPrjData.prjConfigFullNameList:
                if ( StringUtils.findInList( configFullName, configFullNameList ) == -1 ):
                    configFullNameList.append( configFullName )

        configFullNameList.sort()
        self.prjConfigFullNameList = configFullNameList
        return

    def getSlnProjectData( self, prjName, prjAbsPath, wspOld ):
        # tries to get slnPrjData infos from self
        # otherwise tries to get slnPrjData infos from the referenceSolution
        # otherwise it tries to extract them from the project itself
        #
        # prjAbsPath is used only if necessary

        prjNameLwr = prjName.lower()

        #slnPrjData = SlnProjectData()
        if ( self.dictSlnProjectDataByName.has_key( prjNameLwr ) ):
            slnPrjData = self.dictSlnProjectDataByName[ prjNameLwr ]
            #prjPath = self.prjNameRelPathDict[ prjNameLwr ]
            #prjUuid = self.prjNameUuidDict[ prjNameLwr ]
        else:
            #if ( referenceSolution.prjNameRelPathDict.has_key( prjNameLwr ) and referenceSolution.prjNameUuidDict.has_key( prjNameLwr ) ):
            if ( referenceSolution.dictSlnProjectDataByName.has_key( prjNameLwr )):
                slnPrjData = referenceSolution.dictSlnProjectDataByName[ prjNameLwr ]
                if ( slnPrjData.inspectedSlnEntry ):
                    prjAbsPath = referenceSolution.prjNameAbsPathDict[ prjNameLwr ]
                    pass
                else:
                    if ( not slnPrjData.inspectedProject ):
                        prjAbsPath = referenceSolution.prjNameAbsPathDict[ prjNameLwr ]
                        slnPrjData = self.getProjectData( prjName, prjAbsPath, wspOld, True )
                        slnPrjData.inspectedProject = True
                        referenceSolution.dictSlnProjectDataByName[ prjNameLwr ] = slnPrjData
                        referenceSolution.dictSlnProjectDataByUuid[ slnPrjData.prjUuid ] = slnPrjData
            else:
                if ( not prjAbsPath ):
                    if ( not self.prjNameAbsPathDict.has_key( prjNameLwr ) ):
                        if ( not wspOld.prjNameAbsPathDict.has_key( prjNameLwr ) ):
                            raise Exception( 'getSlnProjectData: it is necessary to provide the absolute path to the project \'%s\' in order to retrieve infos from it !' % prjName )
                        else:
                            prjAbsPath = wspOld.prjNameAbsPathDict[ prjNameLwr ]
                    else:
                        prjAbsPath = self.prjNameAbsPathDict[ prjNameLwr ]
                slnPrjData = self.getProjectData( prjName, prjAbsPath, wspOld, True )
                slnPrjData.inspectedProject = True
                referenceSolution.dictSlnProjectDataByName[ prjNameLwr ] = slnPrjData
                referenceSolution.dictSlnProjectDataByUuid[ slnPrjData.prjUuid ] = slnPrjData

        if ( slnPrjData.prjName != prjName ):
            msg = 'getSlnProjectEntries: ERROR: [ %s != %s ] slnPrjData.prjName != prjName !. File: \'%s\'' % ( slnPrjData.prjName, prjName, self.filename )
            raise Exception( msg )

        return slnPrjData

    def getProjectData( self, prjName, prjAbsPath, wspOld, trySlnFirst, knownUuid = '' ):
        #
        # prjAbsPath is used only if necessary

        prjNameLwr = prjName.lower()

        #slnPrjData = SlnProjectData()
        if ( not prjAbsPath ):
            if ( wspOld ):
                prjpath = wspOld.prjNameRelPathDict[ prjNameLwr ]
                if ( not prjpath ):
                    if ( app.allProjectNamesLwrPathsDict.has_key( prjNameLwr ) ):
                        prjAbsPath = app.allProjectNamesLwrPathsDict[ prjNameLwr ]
                    else:
                        raise Exception( 'Workspace::buildProjectData: unable to get infos about the project \'%s\' ' % ( prjName ) )
                else:
                    namedir = os.path.dirname( wspOld.filename )
                    namedir = FileUtils.normDir( namedir, g_internal_unixStyle, True )
                    prjAbsPath = FileUtils.absolutePath( namedir, prjpath, g_internal_unixStyle )
        else:
            if ( app.allProjectNamesLwrPathsDict.has_key( prjNameLwr ) ):
                prjAbsPath2 = app.allProjectNamesLwrPathsDict[ prjNameLwr ]
                if ( prjAbsPath != prjAbsPath2 ):
                    # %%% NOTE: if this will give problems again it is possible to
                    # get the base name of the file and see if it is the same file essentially !
                    # ( an alternative way is also getCompilerFromName(prjAbsPath) and getCompilerFromName(prjAbsPath) and makeDuplicateVcFilename and see the same thing )
                    raise Exception( 'getProjectData: the given prjAbsPath is different than the one in the dictionary. prjName\'%s\' [%s]!=[%s]' % ( prjName, prjAbsPath, prjAbsPath2 ) )

        # first tries to open the vcproj file
        dspFile = DspFile( prjAbsPath )
        slnPrjData = dspFile.getProjectInfos( trySlnFirst, knownUuid )

        #raise Exception( 'Workspace::buildProjectData: not fully implemented yet' )

        return slnPrjData

    def getReferenceInfos( self ):
        # these filenames are solutions filenames
        newFilenameSln = app.options.referenceSolution
        ( root, ext ) = os.path.splitext( newFilenameSln )
        newFilenameSln = root + extSln
        compiler = compilerVc70
        if ( not os.path.exists( self.filename ) ):
            compiler = compilerVc71
            newFilenameSln = DspFile.makeDuplicateVcFilename( newFilenameSln, compilerVc6, compiler, g_internal_unixStyle, True )
            if ( not os.path.exists( newFilenameSln ) ):
                print 'getReferenceInfos: WARNING: reference Workspace \'%s\' does not exists. We will proceed without its information ( i.e. its uuids ). This is safe.' % app.options.referenceSolution
                return

        self.setFilename( newFilenameSln )
        self.setName( newFilenameSln )
        self.setCompilerStrings( compiler )
        self.getInfos( compiler )
        return

    def getInfos( self, newCompiler ):
        self.readlines()
        self.getSlnProjectEntries( newCompiler )
        return

    def getSlnProjectInfos( self, prjName, wspOld ):
        # tries to get the uuid from the referenceSolution before creating a new uuid
        # wspOld is a vc6 workspaces so it doesn't have the uuid info which then has to be created
        # that's why we try that the last
        prjNameLwr = prjName.lower()

        if ( self.prjNameRelPathDict.has_key( prjNameLwr ) ):
            prjPath = self.prjNameRelPathDict[ prjNameLwr ]
            prjUuid = self.prjNameUuidDict[ prjNameLwr ]
        else:
            if ( referenceSolution.prjNameRelPathDict.has_key( prjNameLwr ) and referenceSolution.prjNameUuidDict.has_key( prjNameLwr ) ):
                prjPath = referenceSolution.prjNameRelPathDict[ prjNameLwr ]
                prjUuid = referenceSolution.prjNameUuidDict[ prjNameLwr ]
            else:
                prjPath = wspOld.prjNameRelPathDict[ prjNameLwr ]
                prjUuid = app.getNextUuid( prjName ) # StringUtils.uuidGen()
        return ( prjPath, prjUuid )

    def createSlnProjectEntries( self, wspOld, newCompiler ):
        #creates a solution from scratch

        dirname = os.path.dirname( self.filename )
        dirname = FileUtils.normDir( dirname, g_internal_unixStyle, True )

        lines = []

        if ( newCompiler == compilerVc70 ):
            version = '7.00'
        else:
            version = '8.00'
        line = 'Microsoft Visual Studio Solution File, Format Version %s\n' % version
        lines.append( line )

        #slnPrjData = SlnProjectData()
        for prjName in wspOld.prjNames:
            prjNameLwr = prjName.lower()
            #Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "Actions", "..\..\examples\Actions\Actions_vc70.vcproj", "{7F3664CE-7A4D-4AC1-BB37-B2CD8404813E}"
            # tries to get the uuid from the referenceSolution before creating a new uuid
            #( prjPath, prjUuid ) = self.getSlnProjectInfos( prjName, wspOld )
            slnPrjData = self.getSlnProjectData( prjName, '', wspOld )
            prjAbsPath = slnPrjData.prjAbsPath
            prjAbsPath = DspFile.makeDuplicateVcFilename( prjAbsPath, compilerVc6, newCompiler, g_internal_unixStyle, True )
            ( root, ext ) = os.path.splitext( prjAbsPath )
            prjAbsPath = root + extVcproj
            prjRelPath = FileUtils.relativePath( dirname, prjAbsPath, True, g_internal_unixStyle )

            prjRelPath = FileUtils.normPath( prjRelPath, app.options.unixStyle, g_keepFirstDot_standard, g_MinPathIsDot_True, g_IsDirForSure_False )

            prjUuid = slnPrjData.prjUuid

            line = 'Project(\"{%s}\") = \"%s\", \"%s\", \"{%s}\"\n' % ( g_uuidVisualStudio, prjName, prjRelPath, prjUuid )
            lines.append( line )

            #prjNameLwr = prjName.lower()
            #slnPrjData = self.getSlnProjectData( prjName, '', wspOld )

            if ( newCompiler == compilerVc71 ):
                lines.append( '\tProjectSection(ProjectDependencies) = postProject\n' )

                if ( True or g_workspaceHasPrecedenceOverSolution ):
                    depList = wspOld.dswProjnameDependencyListDict[ prjNameLwr ]
                    for i in range( len( depList ) ):
                        dependencyPrjname = depList[i]
                        slnPrjDataDep = self.getSlnProjectData( dependencyPrjname, '', wspOld )
                        if ( g_options_showNamesForUuids ):
                            line = '\t\t{%s} = {%s} : {%s}\n' % ( slnPrjDataDep.prjUuid, slnPrjDataDep.prjUuid, dependencyPrjname )
                        else:
                            line = '\t\t{%s} = {%s}\n' % ( slnPrjDataDep.prjUuid, slnPrjDataDep.prjUuid )
                        lines.append( line )
                else:
                    for dependencyUuid in slnPrjData.prjDependenciesUuidList:
                        if ( g_options_showNamesForUuids ):
                            dependencyPrjname = self.prjUuidNameDict[ dependencyUuid ]
                            line = '\t\t{%s} = {%s} : {%s}\n' % ( dependencyUuid, dependencyUuid, dependencyPrjname )
                        else:
                            line = '\t\t{%s} = {%s}\n' % ( dependencyUuid, dependencyUuid )
                        lines.append( line )

                lines.append( '\tEndProjectSection\n' )

            lines.append( 'EndProject\n' )

        #       DPCodeReviewSolutionGUID = {00000000-0000-0000-0000-000000000000}
        lines.append( 'Global\n' )
        if ( newCompiler == compilerVc70 ):
            lines.append( '\tGlobalSection(DPCodeReviewSolutionGUID) = preSolution\n' )
            if ( self.uuidDPCodeReview ):
                uuidDPCodeReview = self.uuidDPCodeReview
            else:
                uuidDPCodeReview = '00000000-0000-0000-0000-000000000000'
            line = '\t\tDPCodeReviewSolutionGUID = {%s}\n' % uuidDPCodeReview
            lines.append( line )
            lines.append( '\tEndGlobalSection\n' )

        # configuration names
        lines.append( '\tGlobalSection(SolutionConfiguration) = preSolution\n' )
        n = 0
        if ( 0 == len( self.prjConfigFullNameList ) ):
            raise Exception( 'createSlnProjectEntries: self.prjConfigFullNameList is empty. File: \'%s\'' % ( self.filename ) )
        for configFullName in self.prjConfigFullNameList:
            if ( newCompiler == compilerVc70 ):
                #       ConfigName.1 = GTK Debug
                line = '\t\tConfigName.%d = %s\n' % ( n, configFullName )
            else:
                #               GTK Debug = GTK Debug
                line = '\t\t%s = %s\n' % ( configFullName, configFullName )
            lines.append( line )
            n = n + 1
        lines.append( '\tEndGlobalSection\n' )


        if ( newCompiler == compilerVc70 ):
            #   GlobalSection(ProjectDependencies) = postSolution
            #           {CFD6EAE2-10C6-466D-8BDE-A7E905B842C2}.0 = {AB72FB3C-CF7D-4FB4-B808-BF12C26E8B04}
            lines.append( '\tGlobalSection(ProjectDependencies) = postSolution\n' )
            for prjName in wspOld.prjNames:
                prjNameLwr = prjName.lower()
                slnPrjData = self.getSlnProjectData( prjName, '', wspOld )
                n = 0
                #for dependencyUuid in slnPrjData.prjDependenciesUuidList:
                depList = wspOld.dswProjnameDependencyListDict[ prjNameLwr ]
                for i in range( len( depList ) ):
                    dependencyPrjname = depList[i]
                    #line = '\t\t{%s}.%d = {%s}' % ( slnPrjData.prjUuid, n, dependency )
                    pnam = prjName
                    pdep = dependencyPrjname

                    slnPrjDataDep = self.getSlnProjectData( dependencyPrjname, '', wspOld )
                    if ( g_options_showNamesForUuids ):
                        line = '\t\t{%s}.%d = {%s} : {%s} = {%s}\n' % ( slnPrjData.prjUuid, n, slnPrjDataDep.prjUuid, prjName, dependencyPrjname )
                    else:
                        line = '\t\t{%s}.%d = {%s}\n'               % ( slnPrjData.prjUuid, n, slnPrjDataDep.prjUuid )

                    lines.append( line )
                    n = n + 1
            lines.append( '\tEndGlobalSection\n' )


        #Create a funcion that retrieves all the configurations from dsp files
        # creates a list of projects - configs
        # if os.path.exist( vcproj ) retrieves from vcproj
        # else retrieves from vcproj
        #
        #       GlobalSection(ProjectConfiguration) = postSolution
        #               {7F3664CE-7A4D-4AC1-BB37-B2CD8404813E}.Debug.ActiveCfg = Debug|Win32
        lines.append( '\tGlobalSection(ProjectConfiguration) = postSolution\n' )
        for prjName in wspOld.prjNames:
            #prjNameLwr = prjName.lower()
            slnPrjData = self.getSlnProjectData( prjName, '', wspOld )
            if ( 0 == len( wspOld.prjConfigFullNameList ) ):
                raise Exception( 'updateSlnProjectEntries: wspOld.prjConfigFullNameList is empty. File: \'%s\'' % ( self.filename ) )
            for configFullName in wspOld.prjConfigFullNameList:
                dict = slnPrjData.prjConfigFullNameExCfgPlatfAssocDict
                if ( 0 == len( dict ) ):
                    dict = referenceSolution.dictSlnProjectDataByName[ prjNameLwr ].prjConfigFullNameExCfgPlatfAssocDict
                if ( dict.has_key( configFullName ) ):
                    confignamePlatf = dict[ configFullName ]
                else:
                    configName = configFullName.split( ' ' )[-1]
                    confignamePlatf = dict[ configName ]

                if ( g_options_showNamesForUuids ):
                    line = '\t\t{%s}.%s.ActiveCfg = %s : {%s}\n' % ( slnPrjData.prjUuid, configFullName, confignamePlatf, slnPrjData.prjName )
                    lines.append( line )
                    #line = '\t\t{%s}.%s.Build.0 = %s : {%s}\n'   % ( slnPrjData.prjUuid, configFullName, confignamePlatf, slnPrjData.prjName )
                    #lines.append( line )
                else:
                    line = '\t\t{%s}.%s.ActiveCfg = %s\n'        % ( slnPrjData.prjUuid, configFullName, confignamePlatf )
                    lines.append( line )
                    #line = '\t\t{%s}.%s.Build.0 = %s\n'          % ( slnPrjData.prjUuid, configFullName, confignamePlatf )
                    #lines.append( line )

        lines.append( '\tEndGlobalSection\n' )


        #   GlobalSection(ExtensibilityGlobals) = postSolution
        lines.append( '\tGlobalSection(ExtensibilityGlobals) = postSolution\n' )
        lines.append( '\tEndGlobalSection\n' )

        #   GlobalSection(ExtensibilityAddIns) = postSolution
        lines.append( '\tGlobalSection(ExtensibilityAddIns) = postSolution\n' )
        lines.append( '\tEndGlobalSection\n' )

        lines.append( 'EndGlobal\n' )

        # final update
        self.lines = lines

        return

    def updateSlnProjectEntries( self, wspOld, newCompiler ):
        # modify an existing solution according to the informations in wspOld
        #creates a solution from scratch

        dirname = os.path.dirname( self.filename )
        dirname = FileUtils.normDir( dirname, g_internal_unixStyle, True )

        lines = []

        if ( newCompiler == compilerVc70 ):
            version = '7.00'
        else:
            version = '8.00'
        line = 'Microsoft Visual Studio Solution File, Format Version %s\n' % version
        lines.append( line )

        #slnPrjData = SlnProjectData()
        for prjName in wspOld.prjNames:
            prjNameLwr = prjName.lower()
            #Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "Actions", "..\..\examples\Actions\Actions_vc70.vcproj", "{7F3664CE-7A4D-4AC1-BB37-B2CD8404813E}"
            # tries to get the uuid from the referenceSolution before creating a new uuid
            #( prjPath, prjUuid ) = self.getSlnProjectInfos( prjName, wspOld )
            slnPrjData = self.getSlnProjectData( prjName, '', wspOld )
            prjAbsPath = slnPrjData.prjAbsPath
            prjAbsPath = DspFile.makeDuplicateVcFilename( prjAbsPath, compilerVc6, newCompiler, g_internal_unixStyle, True )
            ( root, ext ) = os.path.splitext( prjAbsPath )
            prjAbsPath = root + extVcproj
            prjRelPath = FileUtils.relativePath( dirname, prjAbsPath, True, g_internal_unixStyle )

            prjRelPath = FileUtils.normPath( prjRelPath, app.options.unixStyle, g_keepFirstDot_standard, g_MinPathIsDot_True, g_IsDirForSure_False )

            prjUuid = slnPrjData.prjUuid
            line = 'Project(\"{%s}\") = \"%s\", \"%s\", \"{%s}\"\n' % ( g_uuidVisualStudio, prjName, prjRelPath, prjUuid )
            lines.append( line )

            #prjNameLwr = prjName.lower()
            #slnPrjData = self.getSlnProjectData( prjName, '', wspOld  )

            if ( newCompiler == compilerVc71 ):
                lines.append( '\tProjectSection(ProjectDependencies) = postProject\n' )

                if ( g_workspaceHasPrecedenceOverSolution ):
                    depList = wspOld.dswProjnameDependencyListDict[ prjNameLwr ]
                    for i in range( len( depList ) ):
                        dependencyPrjname = depList[i]
                        slnPrjDataDep = self.getSlnProjectData( dependencyPrjname, '', wspOld )
                        if ( g_options_showNamesForUuids ):
                            line = '\t\t{%s} = {%s} : {%s}\n' % ( slnPrjDataDep.prjUuid, slnPrjDataDep.prjUuid, dependencyPrjname )
                        else:
                            line = '\t\t{%s} = {%s}\n' % ( slnPrjDataDep.prjUuid, slnPrjDataDep.prjUuid )
                        lines.append( line )
                else:
                    for dependencyUuid in slnPrjData.prjDependenciesUuidList:
                        if ( g_options_showNamesForUuids ):
                            dependencyPrjname = self.prjUuidNameDict[ dependencyUuid ]
                            line = '\t\t{%s} = {%s} : {%s}\n' % ( dependencyUuid, dependencyUuid, dependencyPrjname )
                        else:
                            line = '\t\t{%s} = {%s}\n' % ( dependencyUuid, dependencyUuid )
                        lines.append( line )

                lines.append( '\tEndProjectSection\n' )

            lines.append( 'EndProject\n' )

        #       DPCodeReviewSolutionGUID = {00000000-0000-0000-0000-000000000000}
        lines.append( 'Global\n' )
        if ( newCompiler == compilerVc70 ):
            lines.append( '\tGlobalSection(DPCodeReviewSolutionGUID) = preSolution\n' )
            if ( self.uuidDPCodeReview ):
                uuidDPCodeReview = self.uuidDPCodeReview
            else:
                uuidDPCodeReview = '00000000-0000-0000-0000-000000000000'
            line = '\t\tDPCodeReviewSolutionGUID = {%s}\n' % uuidDPCodeReview
            lines.append( line )
            lines.append( '\tEndGlobalSection\n' )

        # configuration names
        lines.append( '\tGlobalSection(SolutionConfiguration) = preSolution\n' )
        n = 0
        if ( 0 == len( self.prjConfigFullNameList ) ):
            raise Exception( 'updateSlnProjectEntries: self.prjConfigFullNameList is empty. File: \'%s\'' % ( self.filename ) )
        for configFullName in self.prjConfigFullNameList:
            if ( newCompiler == compilerVc70 ):
                #       ConfigName.1 = GTK Debug
                line = '\t\tConfigName.%d = %s\n' % ( n, configFullName )
            else:
                #               GTK Debug = GTK Debug
                line = '\t\t%s = %s\n' % ( configFullName, configFullName )
            lines.append( line )
            n = n + 1
        lines.append( '\tEndGlobalSection\n' )


        if ( newCompiler == compilerVc70 ):
            #   GlobalSection(ProjectDependencies) = postSolution
            #           {CFD6EAE2-10C6-466D-8BDE-A7E905B842C2}.0 = {AB72FB3C-CF7D-4FB4-B808-BF12C26E8B04}
            lines.append( '\tGlobalSection(ProjectDependencies) = postSolution\n' )
            for prjName in wspOld.prjNames:
                prjNameLwr = prjName.lower()
                slnPrjData = self.getSlnProjectData( prjName, '', wspOld )
                n = 0
                if ( g_workspaceHasPrecedenceOverSolution ):
                    depList = wspOld.dswProjnameDependencyListDict[ prjNameLwr ]
                    for i in range( len( depList ) ):
                        dependencyPrjname = depList[i]
                        pnam = prjName
                        pdep = dependencyPrjname
                        slnPrjDataDep = self.getSlnProjectData( dependencyPrjname, '', wspOld )
                        if ( g_options_showNamesForUuids ):
                            line = '\t\t{%s}.%d = {%s} : {%s} = {%s}\n' % ( slnPrjData.prjUuid, n, slnPrjDataDep.prjUuid, pnam, pdep )
                        else:
                            line = '\t\t{%s}.%d = {%s}\n'               % ( slnPrjData.prjUuid, n, slnPrjDataDep.prjUuid )
                        lines.append( line )
                        n = n + 1
                else:
                    for dependencyUuid in slnPrjData.prjDependenciesUuidList:
                        #line = '\t\t{%s}.%d = {%s}' % ( slnPrjData.prjUuid, n, dependency )
                        pnam = self.prjUuidNameDict[ slnPrjData.prjUuid ]
                        pdep = self.prjUuidNameDict[ dependencyUuid ]
                        if ( g_options_showNamesForUuids ):
                            line = '\t\t{%s}.%d = {%s} : {%s} = {%s}\n' % ( slnPrjData.prjUuid, n, dependencyUuid, pnam, pdep )
                        else:
                            line = '\t\t{%s}.%d = {%s}\n'               % ( slnPrjData.prjUuid, n, dependencyUuid )
                        lines.append( line )
                        n = n + 1
            lines.append( '\tEndGlobalSection\n' )


        #Create a funcion that retrieves all the configurations from dsp files
        # creates a list of projects - configs
        # if os.path.exist( vcproj ) retrieves from vcproj
        # else retrieves from vcproj
        #
        #       GlobalSection(ProjectConfiguration) = postSolution
        #               {7F3664CE-7A4D-4AC1-BB37-B2CD8404813E}.Debug.ActiveCfg = Debug|Win32
        lines.append( '\tGlobalSection(ProjectConfiguration) = postSolution\n' )
        for prjName in wspOld.prjNames:
            #prjNameLwr = prjName.lower()
            slnPrjData = self.getSlnProjectData( prjName, '', wspOld )
            if ( 0 == len( self.prjConfigFullNameList ) ):
                raise Exception( 'updateSlnProjectEntries: self.prjConfigFullNameList is empty. File: \'%s\'' % ( self.filename ) )
            for configFullName in self.prjConfigFullNameList:
                dict = slnPrjData.prjConfigFullNameExCfgPlatfAssocDict
                if ( 0 == len( dict ) ):
                    dict = referenceSolution.dictSlnProjectDataByName[ prjNameLwr ].prjConfigFullNameExCfgPlatfAssocDict
                if ( dict.has_key( configFullName ) ):
                    confignamePlatf = dict[ configFullName ]
                else:
                    configName = configFullName.split( ' ' )[-1]
                    confignamePlatf = dict[ configName ]

                if ( g_options_showNamesForUuids ):
                    line = '\t\t{%s}.%s.ActiveCfg = %s : {%s}\n' % ( slnPrjData.prjUuid, configFullName, confignamePlatf, slnPrjData.prjName )
                    lines.append( line )
                    #line = '\t\t{%s}.%s.Build.0 = %s : {%s}\n'   % ( slnPrjData.prjUuid, configFullName, confignamePlatf, slnPrjData.prjName )
                    #lines.append( line )
                else:
                    line = '\t\t{%s}.%s.ActiveCfg = %s\n'        % ( slnPrjData.prjUuid, configFullName, confignamePlatf )
                    lines.append( line )
                    #line = '\t\t{%s}.%s.Build.0 = %s\n'          % ( slnPrjData.prjUuid, configFullName, confignamePlatf )
                    #lines.append( line )
        lines.append( '\tEndGlobalSection\n' )


        #   GlobalSection(ExtensibilityGlobals) = postSolution
        lines.append( '\tGlobalSection(ExtensibilityGlobals) = postSolution\n' )
        lines.append( '\tEndGlobalSection\n' )

        #   GlobalSection(ExtensibilityAddIns) = postSolution
        lines.append( '\tGlobalSection(ExtensibilityAddIns) = postSolution\n' )
        lines.append( '\tEndGlobalSection\n' )

        lines.append( 'EndGlobal\n' )

        # final update
        self.lines = lines

        return

    def replaceProjectEntries( lines, wsp, newCompiler, filename ):
        # makes sure the project entries of a workspace are properly formatted
        # i.e. they must be inside commas and the relative path name written in normal/canonic way

        state = 0
        nPrjs = 0
        for n in range( len( lines ) ):
            line = lines[n]
            m1 = reDswProjectEntryMin.match( line )
            if ( m1 ):
                m2 = reDswProjectEntryFull.match( line )
                if ( not m2 ):
                    raise Exception( 'Bad parsing in workspace %s - line %d: %s' % ( filename, n, line.rstrip() ) )
                prjName = m2.group('prjName')
                prjPath = m2.group('prjPath')
                # pkgOwnr = m2.group('pkgOwnr')

                newline = r'Project: "' + prjName + r'"=' + prjPath + ' - Package Owner=<4>\n'
                if ( newline != line ):
                    print line; print newline
                    if ( newline.strip() == line.strip() ):
                        raise Exception( 'Wrong parsing in workspace %s - line[%d] [%s]  !=  newline[%s]\n [prjName = \'%s\', prjPath = \'%s\'\nBut they differ only by CR: are you using Cywing ? Please report to the author of the script.' % ( filename, n, line.rstrip(), newline, prjName, prjPath ) )
                    else:
                        raise Exception( 'Wrong parsing in workspace %s - line[%d] [%s]  !=  newline[%s]\n [prjName = \'%s\', prjPath = \'%s\'' % ( filename, n, line.rstrip(), newline, prjName, prjPath ) )

                prjPath = StringUtils.trimQuotes( prjPath )
                if ( newCompiler ):
                    newPath = DspFile.makeDuplicateVcFilename( prjPath, wsp.compiler, newCompiler, g_internal_unixStyle, True )
                else:
                    # we need to do this first otherwise problems under Cygwin when g_internal_unixStyle=True but the path starts with r'.\'
                    newPath = FileUtils.normPathSimple( prjPath, g_internal_unixStyle )

                newPath = FileUtils.normPath( newPath, app.options.unixStyle, g_keepFirstDot_standard, g_MinPathIsDot_True, g_IsDirForSure_False ) # g_IsDirForSure_ChkDot

                newline = r'Project: "' + prjName + r'"="' + newPath + '" - Package Owner=<4>\n'

                lines[n] = newline

            # instead the update the dependencies, better to recreate the workspace itself
            #m = reDswProjectEntryFull.match()

            pass
        return lines
    replaceProjectEntries = staticmethod(replaceProjectEntries)

    def fillProjectsLists( self, filterString, ignorecase, addLibraries=False, addGtkLibraries=False ):
        # creates the list of projects forming the workspace
        # the list are creating from the list of all the managed projects *filtered* by the condition
        # of having filterString in their PathNames
        self.prjNames = []
        self.prjNamesDict = {}       # reset but not filled ! Mistake ? @@@
        self.prjAbsPaths = []
        self.prjRelPaths = []
        self.prjNameAbsPathDict = {} # reset but not filled ! Mistake ? @@@
        self.prjNameRelPathDict = {} # reset but not filled ! Mistake ? @@@

        #filterStringLwr = filterString.lower()
        #filterStringDir = os.path.dirname( filterStringLwr )
        #filterStringDir = FileUtils.normDir( filterStringDir, g_internal_unixStyle, True )
        #filterString = filterStringDir
        filterString = FileUtils.normPathSimple( filterString, g_internal_unixStyle )
        if ( ignorecase ):
            filterString = filterString.lower()

        for n in range( len( app.allProjectPathsList )):
            prjName    = app.allProjectNamesList[n]
            absPrjPath = app.allProjectPathsList[n]
            relPrjPath = FileUtils.relativePath( app.currentdir, absPrjPath, True, g_internal_unixStyle )
            relPrjPathLwr = relPrjPath
            if ( ignorecase ):
                relPrjPathLwr = relPrjPathLwr.lower()
            if ( not filterString or relPrjPathLwr.find( filterString ) != -1 ):
                # do not use FileUtils.relativePath because one thing is the path relative to the cwd and different thing is a path relative to the workspace path
                self.addProject( prjName, absPrjPath )

        return

    def fillProjectsListsAddLibraries( self, filteredList ):
        # adds the libraries names in the [vcf_staticLibraries] and [vcf_dynamicLibraries] section to the workspace
        # because any workspace *must* have those libraries in order to compile the projects dependent on it
        if ( filteredList ):
            # filter: we need to add the libraries
            addLibrariesStatic  = True
            addLibrariesDynamic = True
            #JC I turned this to False so that we don't bother with GTK Libs
            addLibrariesGtk     = False

            if ( addLibrariesStatic ):
                for prjName in app.staticLibrariesList:
                    prjNameLwr = prjName.lower()
                    if ( not app.prjNameAbsPathDict.has_key( prjNameLwr ) ):
                        raise Exception ( 'fillProjectsListsAddLibraries: please use the right lettercase for the library list \'%s\'' % prjName )
                    absPrjPath = app.prjNameAbsPathDict[ prjNameLwr ]
                    self.addProject( prjName, absPrjPath )

            if ( addLibrariesDynamic ):
                for prjName in app.dynamicLibrariesList:
                    prjNameLwr = prjName.lower()
                    absPrjPath = app.prjNameAbsPathDict[ prjNameLwr ]
                    self.addProject( prjName, absPrjPath )

            if ( addLibrariesGtk ):
                for prjName in app.gtkLibrariesList:
                    prjNameLwr = prjName.lower()
                    absPrjPath = app.prjNameAbsPathDict[ prjNameLwr ]
                    self.addProject( prjName, absPrjPath )
        else:
            # no filter: all projects are in
            app.prjNameAbsPathDict = self.prjNameAbsPathDict
        return

    def create( self, projNamesList, filterString, ignorecase ): # projPathsList
        # ???
        #if ( not app.options.conformLibraries ):
        #    return

        if ( filterString ):
            self.fillProjectsLists( filterString, ignorecase )

            filteredList = ( filterString and filterString != '.' and filterString != './' and filterString != '.\\' )
            self.fillProjectsListsAddLibraries( filteredList )
        else:
            self.prjNames = projNamesList

        self.copyWorkspaceDependencies( app.options.dependenciesWorkspace )

        workspaceDirname = os.path.dirname( self.filename )
        if ( not os.path.exists( workspaceDirname ) ):
            raise Exception( 'Workspace directory \'%s\' does not exist.\n           It should have been already created !' % workspaceDirname )

        self.createBuildLines( projNamesList, filterString, ignorecase )

        if ( app.options.enableProjectFilesModif ):
            if ( os.path.exists( self.filename ) ):
                os.remove( self.filename )

            fd = file( self.filename, 'w' )
            fd.writelines( self.lines ) # @@@@
            fd.close

        print ' created workspace: %s' % self.filename


    def createBuildLines( self, projNamesList, filterString, ignorecase ): # projPathsList
        workspaceDirname = os.path.dirname( self.filename )

        lines = []
        dependencyList = []

        lines.append( 'Microsoft Developer Studio Workspace File, Format Version 6.00\n' )
        lines.append( '# WARNING: DO NOT EDIT OR DELETE THIS WORKSPACE FILE!\n' )
        lines.append( '\n' )
        lines.append( '###############################################################################\n' )
        lines.append( '\n' )

        #sorting ( this is one way ... )
        #projects = zip( self.prjNames, self.prjRelPaths )
        #projects.sort()
        # for (prjName, relPrjPath) in projects:

        #sorting ( ... and this is another way )
        prjNames = self.prjNames
        prjNamesLwr = []
        if ( g_sort_workspace_ignorecase ):
            # unfortunatly lowercase name goes after so...
            # prjNames.sort()
            for name in prjNames:
                prjNamesLwr.append( name.lower() )
            prjNamesLwr.sort()
        else:
            prjNames.sort()
            for name in self.prjNames:
                prjNamesLwr.append( name.lower() )

        for prjNameLwr in prjNamesLwr:
            if ( not app.allProjectNamesLwrDict.has_key( prjNameLwr ) ):
                prjName = self.prjNamesDict[ prjNameLwr ]
                relPath = self.prjNameRelPathDict[ prjNameLwr ]
                app.addProject( prjName, prjNameLwr, workspaceDirname, relPath )
                #app.allProjectNamesList.append( prjName )
                #app.allProjectNamesLwrDict[ prjNameLwr ] = prjName
                #absPrjPath = FileUtils.absolutePath( app.currentdir, root + sep + fullname, g_internal_unixStyle )
                #app.allProjectPathsList.append( absPrjPath )
                #app.allProjectNamesLwrPathsDict[ prjNameLwr ] = absPrjPath

            prjName = app.allProjectNamesLwrDict[ prjNameLwr ]
            prjAbsPath = app.allProjectNamesLwrPathsDict[ prjNameLwr ]

            relPrjPath = FileUtils.relativePath( workspaceDirname, prjAbsPath, True, g_internal_unixStyle )

            #relPrjPath = self.prjNameRelPathDict[ prjNameLwr ]

            relPrjPath = FileUtils.normPath( relPrjPath, app.options.unixStyle, g_keepFirstDot_standard, g_MinPathIsDot_True, g_IsDirForSure_False ) # g_IsDirForSure_ChkDot ?

            #'Project: "%s"="%s" - Package Owner=<4>\n'
            prjLine = r'Project: "' + prjName + r'"="' + relPrjPath + '" - Package Owner=<4>\n'
            lines.append( prjLine )


            lines.append( '\n' )
            lines.append( 'Package=<5>\n' )
            lines.append( '{{{\n' )
            lines.append( '}}}\n' )
            lines.append( '\n' )
            lines.append( 'Package=<4>\n' )
            lines.append( '{{{\n' )

            #'    Begin Project Dependency'
            #'    Project_Dep_Name Dialogs'
            #'    End Project Dependency'

            # some projects need all the necessary dependencies ( hardcoded )
            dependencyList = []
            if ( prjNameLwr == 'examples' ): # e.g. 'examples'
                dependencyListLib = self.buildDependencyListItem( 'ApplicationKitDLL' )
                dependencyList.append( dependencyListLib )
                dependencyAllProjects = self.calcDependencyListAllProjects( prjName, prjNames, g_dependencyFilterExamplesProject )
                dependencyList += dependencyAllProjects
            else:
                # disabled the dependencies creation: now they are all copied from app.options.dependenciesWorkspace 2004/04/08
                #dependencyList = self.calcDependencyList( prjName )
                #if ( not dependencyList ):
                # for projects without dependencies, copies them from app.options.dependenciesWorkspace
                if ( self.dependencies ):
                    if ( self.dependencies.has_key( prjNameLwr ) ):
                        dependencyList = self.dependencies[ prjNameLwr ]


            for dep in dependencyList:
                lines.append( '    Begin Project Dependency\n' )
                lines.append( '    Project_Dep_Name ' + dep + '\n' )
                lines.append( '    End Project Dependency\n' )

            lines.append( '}}}\n' )
            lines.append( '\n' )
            lines.append( '###############################################################################\n' )
            lines.append( '\n' )

            pass

        # last part
        lines.append( 'Global:\n' )
        lines.append( '\n' )
        lines.append( 'Package=<5>\n' )
        lines.append( '{{{\n' )
        lines.append( '}}}\n' )
        lines.append( '\n' )
        lines.append( 'Package=<3>\n' ) # note: 3 not 4
        lines.append( '{{{\n' )
        lines.append( '}}}\n' )
        lines.append( '\n' )
        lines.append( '###############################################################################\n' )
        lines.append( '\n' )

        self.lines = lines

        return

    def copyWorkspaceDependencies( self, dependencyWorkspaceName ):
        """ Copies all dependencies from a workspace considered master for this"""
        self.dependencies.clear()

        if ( not dependencyWorkspaceName ):
            return

        dependencyWorkspaceDirname = os.path.dirname( dependencyWorkspaceName )
        if ( not os.path.exists( dependencyWorkspaceDirname ) ):
            raise Exception( 'Dependency Workspace directory \'%s\' does not exist !\n' % dependencyWorkspaceDirname )
        if ( not os.path.exists( dependencyWorkspaceName ) ):
            raise Exception( 'Dependency Workspace \'%s\' does not exist !\n' % dependencyWorkspaceName )

        fw = file( dependencyWorkspaceName, 'r' )
        wlines = fw.readlines()
        fw.close

        dependencyList = []
        state = 0
        nPrjs = 0
        for n in range( len( wlines ) ):
            line = wlines[n]

            if ( state == 0 ):
                dependencyList = []
                m = reDswProjectEntryMin.match( line )
                if ( m ):
                    prjName = m.group('prjName')
                    if ( not prjName ):
                        raise Exception( 'Error: no project extracted from line [%d]: %s' % ( n, line.rstrip() ) )
                    nPrjs += 1
                    state = 1
            elif ( state == 1 and re.match( 'Package=<4>', line ) ):
                state = 2
            elif ( state == 2 and re.match( '{{{', line ) ):
                state = 3
            elif ( state == 3 ):
                if ( re.match( '}}}', line ) ):
                    prjNameLwr = prjName.lower()
                    self.dependencies[ prjNameLwr ] = dependencyList
                    state = 0
                else:
                    m_dsw_projectDependency_entry = re_dsw_projectDependency_entry.match( line )
                    if ( m_dsw_projectDependency_entry ):
                        projnamedep = m_dsw_projectDependency_entry.group( 'projnamedep' ) #@@@
                        dependencyList.append( projnamedep )
            else:
                pass

        nDeps = len( self.dependencies )
        if ( nDeps != nPrjs ):
            raise Exception( 'dependencies[%d] != nPrjs[%d] ( state[%d] ). Workspace: %s' % ( nDeps, nPrjs, state, dependencyWorkspaceName ) )
        elif ( state != 0 ):
            raise Exception( 'wrong state: [%d]  ( but dependencies[%d] == nPrjs[%d] ). Workspace: %s' % ( state, nDeps, nPrjs, dependencyWorkspaceName ) )

        return

    def calcDependencyListAllProjects( self, projectName, prjNames, filterString ):
        # for a generic projectName it calculates all its dependencies and puts them in string
        #workspaceDirname = os.path.dirname( self.filename )

        dependencyAllProjects = []
        projectNameLwr = projectName.lower()
        filterString = filterString.lower()
        for prjName in prjNames:
            prjNameLwr = prjName.lower()
            # path relative to this workspace
            #relPrjPath = self.prjNameRelPathDict[ prjNameLwr ]

            #prjAbsPath = app.allProjectNamesLwrPathsDict[ prjNameLwr ]
            #relPrjPath = FileUtils.relativePath( workspaceDirname, prjAbsPath, True, g_internal_unixStyle )

            # path relative to app.currentdir
            absPrjPath = self.prjNameAbsPathDict[ prjNameLwr ]
            relPrjPath = FileUtils.relativePath( app.currentdir, absPrjPath, True, g_internal_unixStyle )
            relPrjPath = relPrjPath.lower()
            relPrjPath = relPrjPath.replace("\\", "/")
            if ( not filterString or relPrjPath.find( filterString ) != -1 ): # @@@
                if ( prjName.lower() != projectNameLwr ):
                    dependencyAllProjects.append( self.buildDependencyListItem( prjName ) )
        return dependencyAllProjects

    def calcDependencyList( self, project ):
        # calc the dependency string of the library that a library project is dependent of
        # this string generally consists of the only library project that must be compiled before the library project itself
        lib = ''
        dependencyList = []
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
        #    dependencyList.append( self.buildDependencyListItem( lib ) )
        if lib:
            dependencyList.append( self.buildDependencyListItem( lib ) )

        return dependencyList

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

    def buildDependencyListItem( self, project ):
        # build the dependency string of a project to be used in a workspace
        #dependencyStringListItem = ''
        #dependencyStringListItem += '    Begin Project Dependency\n'
        #dependencyStringListItem += '    Project_Dep_Name ' + project + '\n'
        #dependencyStringListItem += '    End Project Dependency\n'
        #return dependencyStringListItem
        return project

    def conformAllLibraries( self ):
        #loop on all libraries files and sinchronize their content
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

                nameMaster = StringUtils.trimQuotes( nameMaster )
                nameMaster = nameMaster.strip()

                nameChanged = StringUtils.trimQuotes( nameChanged )
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

                absPathChanged = self.prjNameAbsPathDict[ nameChanged.lower() ]
                absPathMaster  = self.prjNameAbsPathDict[ nameMaster.lower()  ]

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
        #synchronize the content between two libraries files
        dr = DspFile( filenameMaster )
        dr.readlines()
        targetSection = dr.readTargetSection()

        dw = DspFile( filenameChanged )
        dw.readlines()
        configurationSection = dw.readConfigurationSection()

        tmpFilename = dw.replaceAllSections( configurationSection, targetSection )

        dw.replaceWithFile( tmpFilename, False, app.options.enableProjectFilesModif )

        nameMaster  = os.path.basename ( filenameMaster )
        nameChanged = os.path.basename ( filenameChanged )
        print ' conformed library [ %-30s --> %-30s ]' % ( nameMaster, nameChanged )

        return





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

        app.logFileOpen( False )

        self.listProjects()

        self.reformatProjects()

        if ( not singleFile and not testingParse ):
            self.conformLibraries()

        self.synchronizeProjects()

        if ( not singleFile and not testingParse ):
            self.createWorkspaces()
            self.duplicateWorkspaces()
            pass

        nFiles = app.changedFilesTot + app.unchangedFilesTot + app.createdFilesTot
        print '\n Total: %d dsp file(s) processed. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.changedFilesTot, app.unchangedFilesTot, app.createdFilesTot )

        return

    def listProjects( self ):
        # lists all the project in the allowed/not excluded subdirectories
        # this function must be always active

        print '\n listing projects ...\n'

        app.allProjectNamesList = []
        app.allProjectPathsList = []
        app.allProjectNamesLwrDict = {}
        app.allProjectNamesLwrPathsDict = {}

        sep = FileUtils.getNormSep( g_internal_unixStyle )

        singleFile = ( app.options.filename != '' )

        app.resetCounts()
        nFiles = 0
        for filename in self.walk_files( root, app.options.recurse ):
            allowed = StringUtils.isExtensionAllowed( filename, app.allowedExtensionsList )
            if ( allowed ):
                # skip filenames like: file_vc70.dsp or file_vc71.dsp
                filename = FileUtils.normPath( filename, g_internal_unixStyle )

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
                    fullname = FileUtils.normPath( fullname, g_internal_unixStyle )

                    #if ( app.options.backupFiles ): # before uncommenting verify what it correct to control this with this option
                    #    FileUtils.backup( fullname )
                    #if ( 0 < app.options.verbose ):
                    #    print FileUtils.relativePath( app.currentdir, fullname, True, g_internal_unixStyle )
                    dsp = DspFile( fullname )
                    #dsp.reformat()

                    prjName = dsp.readTrueProjectName()
                    prjNameLwr = prjName.lower()
                    app.addProject( prjName, prjNameLwr, app.currentdir, root + sep + fullname )
                    #app.allProjectNamesList.append( prjName )
                    #app.allProjectNamesLwrDict[ prjNameLwr ] = prjName
                    #absPrjPath = FileUtils.absolutePath( app.currentdir, root + sep + fullname, g_internal_unixStyle )
                    #app.allProjectPathsList.append( absPrjPath )
                    #app.allProjectNamesLwrPathsDict[ prjNameLwr ] = absPrjPath

                    #if ( app.options.enableVcfSpecific ):
                    #    dsp.duplicateVcDsps()
        return

    def reformatProjects( self ):
        if ( testingParse ):
            return

        print '\n reformatting dps projects ...\n'

        app.resetCounts()
        nFiles = 0

        if ( app.getProjectDataForEachProject ):
            wspDummy = Workspace( 'dummysolution.sln', False ) # we will never save this !

        for filename in app.allProjectPathsList:
            nFiles += 1

            fullname = os.path.join( root, filename )
            fullname = FileUtils.normPath( fullname, g_internal_unixStyle )

            if ( app.options.backupFiles ):
                FileUtils.backup( fullname )
            if ( 0 < app.options.verbose ):
                print FileUtils.relativePath( app.currentdir, fullname, True, g_internal_unixStyle )
            dsp = DspFile( fullname )
            dsp.reformat()

            # this is done in order to have the table referenceSolution.dictSlnProjectDataByName filled up gradually
            if ( app.getProjectDataForEachProject ):
                wspDummy.getSlnProjectData( dsp.trueProjectName, fullname, None )
                if ( referenceSolution.dictSlnProjectDataByName[ dsp.trueProjectName.lower() ].prjAbsPath != fullname ):
                    raise Exception( 'reformatProjects: referenceSolution.dictSlnProjectDataByName not properly added of infos for the project \'%s\'' % dsp.trueProjectName )

            #if ( app.options.enableVcfSpecific ):
            #    dsp.duplicateVcDsps()

            pass

        if ( 0 < app.options.verbose ):
            print ' %s dsp file(s) processed. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.changedFiles, app.unchangedFiles, app.createdFiles)
            #print ' %s dsp file(s) processed [errors on %d, warnings on %d of them]. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.numErrors, app.numWarnings, app.changedFiles, app.unchangedFiles, app.createdFiles)

        return

    def synchronizeProjects( self ):
        #if ( testingParse ):
        #    return

        print '\n synchronizing other compilers projects ...\n'

        app.resetCounts()
        nFiles = 0
        for filename in app.allProjectPathsList:
            nFiles += 1

            fullname = os.path.join( root, filename )
            fullname = FileUtils.normPath( fullname, g_internal_unixStyle )

            #if ( app.options.backupFiles ): # before uncommenting verify what it correct to control this with this option
            #    FileUtils.backup( fullname )
            if ( 0 < app.options.verbose ):
                print FileUtils.relativePath( app.currentdir, fullname, True, g_internal_unixStyle )
            dsp = DspFile( fullname )
            #dsp.reformat()

            # reads some infos from inside the file ( maybe not necessary )
            prjName = dsp.readTrueProjectName()

            if ( app.options.enableVcfSpecific ):
                dsp.duplicateVcDsps()

            pass

        if ( 0 < app.options.verbose ):
            print ' %s project file(s) processed. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.changedFiles, app.unchangedFiles, app.createdFiles)
            #print ' %s dsp file(s) processed [errors on %d, warnings on %d of them]. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.numErrors, app.numWarnings, app.changedFiles, app.unchangedFiles, app.createdFiles)

        return

    def conformLibraries( self ):
        if ( testingParse ):
            return

        if ( app.options.conformLibraries ):
            print '\n conforming libraries ...\n'
            workspaceName = FileUtils.absolutePath( app.currentdir, 'dummy', g_internal_unixStyle )
            workspaceCL = Workspace( workspaceName )
            workspaceCL.conformAllLibraries()
        return

    def createWorkspaces( self ):
        if ( testingParse ):
            return

        if ( app.options.enableVcfSpecific and app.options.createWorkspaces ):
            print '\n creating workspaces ...\n'

            app.resetCounts()
            nFiles = 0

            # creates
            for workspaceName in app.createWorkspacesList:
                nFiles += 1
                workspacePath = FileUtils.absolutePath( app.currentdir, workspaceName, g_internal_unixStyle )
                workspace = Workspace( workspacePath )
                ( workspaceName, ext ) = os.path.splitext( os.path.basename( workspacePath ) )
                workspaceName = workspaceName.lower()
                workspace.create( app.allProjectNamesList, g_tableFilterWorkspacesCreation[workspaceName], True ) # app.allProjectPathsList,
                workspace.duplicateVcs( True ) # %%% was False, but why not to update and reformat the original ?

            if ( 0 < app.options.verbose ):
                print ' %s workspace file(s) processed. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.changedFiles, app.unchangedFiles, app.createdFiles)
                #print ' %s dsp file(s) processed [errors on %d, warnings on %d of them]. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.numErrors, app.numWarnings, app.changedFiles, app.unchangedFiles, app.createdFiles)

        return

    def duplicateWorkspaces( self ):
        if ( app.options.enableVcfSpecific and app.options.duplicateWorkspaces ):
            print '\n duplicating workspaces ...\n'

            app.resetCounts()
            nFiles = 0

            #blackBoxWorkspaceName = './BlackBox/BlackBox.dsw'
            #xmakeWorkspaceName    = './xmake/xmake.dsw'
            for workspaceName in app.duplicateWorkspacesList:
                nFiles += 1
                workspacePath = FileUtils.absolutePath( app.currentdir, workspaceName, g_internal_unixStyle )
                workspace = Workspace( workspacePath )
                workspace.duplicateVcs( True )

            if ( 0 < app.options.verbose ):
                print ' %s workspace file(s) processed. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.changedFiles, app.unchangedFiles, app.createdFiles)
                #print ' %s dsp file(s) processed [errors on %d, warnings on %d of them]. [changed: %s, unchanged: %s, created: %s]' % (nFiles, app.numErrors, app.numWarnings, app.changedFiles, app.unchangedFiles, app.createdFiles)

        return



if __name__ == '__main__':
    root = '.'

    app = DspApp()

    if ( app.options.prompt ):
        raw_input( '\n  Press enter to continue ( Ctrl+C to exit ) ... ')

    # it is not accepted in a different way under cygwin
    #app.currentdir = app.currentdir.replace( '\\', '/' )
    #app.currentdir = app.currentdir.replace( '//', '/' )
    os.chdir( app.currentdir )

    # get some infos about many projects
    referenceSolution = Workspace( app.options.referenceSolution, False )
    if ( not testingParse ):
        referenceSolution.getReferenceInfos()
        app.getProjectDataForEachProject = ( 0 == len( referenceSolution.dictSlnProjectDataByName ) ) #%%%$$$

    walker = Walker()
    walker.job()

    app.logFileClose()

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
        Here we say that we tend to remove the /Fd:pathfilename.pdb option because vc6 tends to do it

    7) The way a configuration of a dsp project is considered debug versus release is still naive
        so it might fail if a user doesn't call it Debug
        This can be easily fixed. See the function checkSetDebug

    8) Dependencies: they are only managed by copy from the app.options.dependenciesWorkspace
        Which is a master workspace created only for this purpose.
        this doesn't let the program to ensure certain dependency are always there, but it is
        the simplest way to manage them in the correct way.

Limitations:
    1) The options work better form the configuration files
        because I didn't look yet on how get options from the command line without argument

    2) A program database option is mosly enabled/disabled by the /debug option ( generate debug info )
        which is present or in the #ADD LINK32 line or in the #SUBTRACT LINK32 line
        But this program doesn't affect (create) any SUBTRACT line if it doesn't exist yet

    3) It is possible to change the option from unixStyle = True --> False
        For this it is necessary to change the value of app.options.unixStyle
        Do not touch the option: g_internal_unixStyle otherwise the script will not work under Cygwin
        Suggestion: keep app.options.unixStyle = False because vc70 does not read right the unix style from its solution files

        Note: some interesting things abouit VisualStudio format:
            vc7 files have the formats:
                for any configuration options:
                    subidr:
                        ".\dirname\subir/"
                    file:
                        ".\dirname\subir\filetitle.ext"
                and the same for the <File entries too
            se we better try to keep the same format for vc6 project files too
            The same is true for Project: entries in the workspaces dsw and sln
            Problem:
                 vc7 always put '/' at the end of a directory name when it creates one project file,
                 but custom build cannot copy any file into a path like that !
                 so not any variable like $(InputPath) or $(OutDir) can have that format !
                 Some guys over there they should decide what they want to do with their filesystems !

    4) The script *requires* that the names of the source files ( cpp/h ) are unique (no matter what their case is)
        This is not a strong limitation and let the script to retrieve the informations about files
        by their name only i.e. even if their relative path has been changed

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

    2) Option fixFilenamePostfix
        When vc7 comvert from a dsp files it is wrong with the created options: OutputFile and ProgramDatabaseFile
        It does not to copy them right from the dsp !

To do:
        See Note[*] around this script
        COMPARE with vc71 project
        create vc70 project from dsp
        ( plese remember:

        Creates a list of projects ( for vc70 and vc71 ) that can be updated from the vcproj version (vc7x) instead than from the dsp version (vc6)
            At this moment it is responsability of the person having the vcproj to keep updated the vc6 version

"""
