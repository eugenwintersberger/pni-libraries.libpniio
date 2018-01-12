PROJECT_NAME           = @CMAKE_PROJECT_NAME@
PROJECT_NUMBER         =
OUTPUT_DIRECTORY       = ./
CREATE_SUBDIRS         = NO
OUTPUT_LANGUAGE        = English
BRIEF_MEMBER_DESC      = YES
REPEAT_BRIEF           = NO
ALWAYS_DETAILED_SEC    = NO
INLINE_INHERITED_MEMB  = NO
FULL_PATH_NAMES        = NO
SHORT_NAMES            = NO
JAVADOC_AUTOBRIEF      = NO
MULTILINE_CPP_IS_BRIEF = NO
INHERIT_DOCS           = YES
SEPARATE_MEMBER_PAGES  = NO
TAB_SIZE               = 4
OPTIMIZE_OUTPUT_FOR_C  = YES           
BUILTIN_STL_SUPPORT    = YES
DISTRIBUTE_GROUP_DOC   = NO
SUBGROUPING            = YES
         
#---------------------------------------------------------------------------
# Build related configuration options
#---------------------------------------------------------------------------
EXTRACT_ALL            = YES
EXTRACT_PRIVATE        = YES
EXTRACT_STATIC         = YES
EXTRACT_LOCAL_CLASSES  = YES
EXTRACT_LOCAL_METHODS  = YES
HIDE_UNDOC_MEMBERS     = NO
HIDE_UNDOC_CLASSES     = NO
HIDE_FRIEND_COMPOUNDS  = NO
HIDE_IN_BODY_DOCS      = NO
INTERNAL_DOCS          = NO
CASE_SENSE_NAMES       = YES
HIDE_SCOPE_NAMES       = NO
SHOW_INCLUDE_FILES     = YES
INLINE_INFO            = YES
SORT_MEMBER_DOCS       = YES
SORT_BRIEF_DOCS        = NO
SORT_BY_SCOPE_NAME     = NO
GENERATE_TODOLIST      = YES
GENERATE_TESTLIST      = YES
GENERATE_BUGLIST       = YES
GENERATE_DEPRECATEDLIST= YES
MAX_INITIALIZER_LINES  = 30
SHOW_USED_FILES        = YES

#---------------------------------------------------------------------------
# configuration options related to warning and progress messages
#---------------------------------------------------------------------------
QUIET                  = NO
WARNINGS               = YES
WARN_IF_UNDOCUMENTED   = YES
WARN_IF_DOC_ERROR      = YES
WARN_NO_PARAMDOC       = YES


#---------------------------------------------------------------------------
# configuration options related to the input files
#---------------------------------------------------------------------------
INPUT                  = @PROJECT_SOURCE_DIR@/src
RECURSIVE              = YES
EXCLUDE_SYMLINKS       = NO
EXAMPLE_PATH           = examples
EXAMPLE_PATTERNS       =
EXAMPLE_RECURSIVE      = NO
IMAGE_PATH             = @CMAKE_CURRENT_SOURCE_DIR@/images
INPUT_FILTER           = 
FILE_PATTERNS          = *.hpp
FILTER_PATTERNS        = 
FILTER_SOURCE_FILES    = NO

#---------------------------------------------------------------------------
# configuration options related to source browsing
#---------------------------------------------------------------------------
SOURCE_BROWSER         = NO
INLINE_SOURCES         = NO
STRIP_CODE_COMMENTS    = YES
REFERENCED_BY_RELATION = NO
REFERENCES_RELATION    = NO
REFERENCES_LINK_SOURCE = YES
USE_HTAGS              = NO
VERBATIM_HEADERS       = YES

#---------------------------------------------------------------------------
# configuration options related to the alphabetical class index
#---------------------------------------------------------------------------
ALPHABETICAL_INDEX     = YES
COLS_IN_ALPHA_INDEX    = 5
IGNORE_PREFIX          =
 
#---------------------------------------------------------------------------
# configuration options related to the HTML output
#---------------------------------------------------------------------------
GENERATE_HTML          = YES
HTML_OUTPUT            = html
HTML_FILE_EXTENSION    = .html
HTML_HEADER            =
HTML_FOOTER            =
HTML_STYLESHEET        =
GENERATE_HTMLHELP      = YES
HHC_LOCATION           =
GENERATE_CHI           = NO
BINARY_TOC             = NO
TOC_EXPAND             = NO
DISABLE_INDEX          = NO
ENUM_VALUES_PER_LINE   = 4
GENERATE_TREEVIEW      = NO
TREEVIEW_WIDTH         = 250
SEARCHENGINE           = NO

#---------------------------------------------------------------------------
# Configuration options related to the preprocessor
#---------------------------------------------------------------------------
ENABLE_PREPROCESSING   = YES
MACRO_EXPANSION        = NO
EXPAND_ONLY_PREDEF     = NO
SEARCH_INCLUDES        = YES
INCLUDE_PATH           =
INCLUDE_FILE_PATTERNS  = 
PREDEFINED             =
EXPAND_AS_DEFINED      =
SKIP_FUNCTION_MACROS   = YES
            
#---------------------------------------------------------------------------
# Configuration::additions related to external references
#---------------------------------------------------------------------------
TAGFILES               =
GENERATE_TAGFILE       =
ALLEXTERNALS           = NO
EXTERNAL_GROUPS        = YES
PERL_PATH              = /usr/bin/perl
            
#---------------------------------------------------------------------------
# Configuration options related to the dot tool
#---------------------------------------------------------------------------
CLASS_DIAGRAMS         = YES
HIDE_UNDOC_RELATIONS   = YES
HAVE_DOT               = YES
CLASS_GRAPH            = YES
COLLABORATION_GRAPH    = YES
GROUP_GRAPHS           = YES
UML_LOOK               = NO
TEMPLATE_RELATIONS     = NO
INCLUDE_GRAPH          = NO
INCLUDED_BY_GRAPH      = NO
CALL_GRAPH             = NO
CALLER_GRAPH           = NO
GRAPHICAL_HIERARCHY    = YES
DIRECTORY_GRAPH        = YES
DOT_IMAGE_FORMAT       = png
DOT_PATH               =
DOTFILE_DIRS           =
MAX_DOT_GRAPH_DEPTH    = 50 
DOT_TRANSPARENT        = NO
DOT_MULTI_TARGETS      = YES
GENERATE_LEGEND        = YES
DOT_CLEANUP            = YES

GENERATE_LATEX = NO

DOXYFILE_ENCODING      = UTF-8
TYPEDEF_HIDES_STRUCT   = NO
EXTRACT_ANON_NSPACES   = NO
FORCE_LOCAL_INCLUDES   = NO
SORT_MEMBERS_CTORS_1ST = NO
SORT_GROUP_NAMES       = NO
SHOW_FILES             = YES
SHOW_NAMESPACES        = YES
INPUT_ENCODING         = UTF-8
EXCLUDE_SYMBOLS        = 
HTML_COLORSTYLE_HUE    = 220
HTML_COLORSTYLE_SAT    = 100
HTML_COLORSTYLE_GAMMA  = 80
HTML_TIMESTAMP         = YES
HTML_DYNAMIC_SECTIONS  = NO
GENERATE_DOCSET        = NO
DOCSET_FEEDNAME        = 'Documentation for @CMAKE_PROJECT_NAME@ @LIBRARY_VERSION@'
DOCSET_BUNDLE_ID       = org.doxygen.@CMAKE_PROJECT_NAME@-@LIBARAY_VERSION@
DOCSET_PUBLISHER_ID    = org.doxygen.DESY
DOCSET_PUBLISHER_NAME  = DESY                      
GENERATE_QHP           = NO
EXT_LINKS_IN_WINDOW    = NO
FORMULA_FONTSIZE       = 10
FORMULA_TRANSPARENT    = YES
SERVER_BASED_SEARCH    = NO
LATEX_SOURCE_CODE      = NO
MSCGEN_PATH            =
DOT_NUM_THREADS        = 0
DOT_FONTSIZE           = 10
DOT_FONTPATH           =
DOT_GRAPH_MAX_NODES    = 50
USE_MATHJAX = NO
WARN_FORMAT            = '$file:$line: $text'

#---------------------------------------------------------------------------
# Configuration options related to the XML output
#---------------------------------------------------------------------------

# If the GENERATE_XML tag is set to YES doxygen will generate an XML file that
# captures the structure of the code including all documentation.
# The default value is: NO.

GENERATE_XML           = YES

# The XML_OUTPUT tag is used to specify where the XML pages will be put. If a
# relative path is entered the value of OUTPUT_DIRECTORY will be put in front of
# it.
# The default directory is: xml.
# This tag requires that the tag GENERATE_XML is set to YES.

XML_OUTPUT             = xml

# If the XML_PROGRAMLISTING tag is set to YES doxygen will dump the program
# listings (including syntax highlighting and cross-referencing information) to
# the XML output. Note that enabling this will significantly increase the size
# of the XML output.
# The default value is: YES.
# This tag requires that the tag GENERATE_XML is set to YES.

XML_PROGRAMLISTING     = YES
