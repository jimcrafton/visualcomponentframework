#.autodepend

DIRS=Actions \
    AdvancedAlignment.exe \
    Alignment.exe \
    Anchors.exe \
    ApplicationIcons.exe \
    Conditions.exe \
    CopyAndPaste.exe \
    DateTimeUI.exe \
    DatesAndTime.exe \
    Dictionaries.exe \
    Directories.exe \
    DocViewAdvanced.exe \
    DocViewBasics.exe \
    DragAndDrop.exe \
    EventBasics.exe \
    Examples.exe \
    FilesAndDirectories.exe \
    GraphicsAndMouseMoves.exe \
    GraphicsBasics.exe \
    HeavyAndLight.exe \
    HelloWorld.exe \
    HelloWorld2.exe \
    HelloWorld3.exe \
    ImageBasics.exe \
    ImageViewer.exe \
    Labels.exe \
    ListBox.exe \
    Localization.exe \
    MVCBasics.exe \
    OpenGLShapes.exe \
    Processes.exe \
    ProgressBars.exe \
    QTPlayer.exe \
    Reflection.exe \
    Scrolling.exe \
    SharedLibraries.exe \
    SketchIt.exe \
    Sliders.exe \
    Splitters.exe \
    Strings.exe \
    StrokesAndFills.exe \
    Tables.exe \
    TextLayout.exe \
    ThreadBasics.exe \
    ThreadsInGUI.exe \
    Toolbars.exe \
    TreeListControls.exe \
    VisualFormFiles.exe \
    WorkingWithEnumerators.exe \
    dummybcb.exe \
    AdvancedUI.exe \
    Colors.exe \
    Controls.exe \
    Printing.exe \
    SysTray.exe \
    Transformations.exe \
    TeXLabel.exe 

BUILDALL:: $(DIRS)
    -&cd $(<B)
    -&bmake -f ..\generic_bcc.mak
    -&cd ..
 
 ..exe:
    -&cd $(@B)
    -&bmake -f ..\generic_bcc.mak
    -&cd ..
    