###########################################################
#
#CVS Log info
#$Log$
#Revision 1.2  2003/02/26 04:30:25  ddiego
#merge of code in the devmain-0-5-9 branch into the current tree.
#most additions are in the area of the current linux port, but the major
#addition to this release is the addition of a Condition class (currently
#still under development) and the change over to using the Delegate class
#exclusively from the older event handler macros.
#
#Revision 1.1.2.3  2003/02/08 17:55:44  ddiego
#modified the makefiles to have cvs Log entries, so we can keepo track of
#whats going on :)
#
#
#
#
#Object files for the GraphicsKit 
#
###########################################################



###########################################################
#Debug files
###########################################################

$(OUTDIR_GK_D)/GraphicsKit.o : $(SRC_GRF)/GraphicsKit.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/GraphicsKit.cpp -o $(OUTDIR_GK_D)/GraphicsKit.o
	

$(OUTDIR_GK_D)/AbstractImage.o : $(SRC_GRF)/AbstractImage.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/AbstractImage.cpp -o $(OUTDIR_GK_D)/AbstractImage.o
	
$(OUTDIR_GK_D)/BasicFill.o : $(SRC_GRF)/BasicFill.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/BasicFill.cpp -o $(OUTDIR_GK_D)/BasicFill.o
	
$(OUTDIR_GK_D)/BasicStroke.o : $(SRC_GRF)/BasicStroke.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/BasicStroke.cpp -o $(OUTDIR_GK_D)/BasicStroke.o
	
$(OUTDIR_GK_D)/Color.o : $(SRC_GRF)/Color.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/Color.cpp -o $(OUTDIR_GK_D)/Color.o
	
$(OUTDIR_GK_D)/Font.o : $(SRC_GRF)/Font.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/Font.cpp -o $(OUTDIR_GK_D)/Font.o
	
$(OUTDIR_GK_D)/FontState.o : $(SRC_GRF)/FontState.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/FontState.cpp -o $(OUTDIR_GK_D)/FontState.o
	
$(OUTDIR_GK_D)/GlyphCollection.o : $(SRC_GRF)/GlyphCollection.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/GlyphCollection.cpp -o $(OUTDIR_GK_D)/GlyphCollection.o
	
$(OUTDIR_GK_D)/GraphicsContext.o : $(SRC_GRF)/GraphicsContext.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/GraphicsContext.cpp -o $(OUTDIR_GK_D)/GraphicsContext.o
	
$(OUTDIR_GK_D)/GraphicsObject.o : $(SRC_GRF)/GraphicsObject.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/GraphicsObject.cpp -o $(OUTDIR_GK_D)/GraphicsObject.o
	
$(OUTDIR_GK_D)/GraphicsToolKit.o : $(SRC_UTILS)/GraphicsToolKit.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_UTILS)/GraphicsToolKit.cpp -o $(OUTDIR_GK_D)/GraphicsToolKit.o
	
$(OUTDIR_GK_D)/ImageEvent.o : $(SRC_EVENT)/ImageEvent.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_EVENT)/ImageEvent.cpp -o $(OUTDIR_GK_D)/ImageEvent.o
	
$(OUTDIR_GK_D)/Matrix2D.o : $(SRC_GRF)/Matrix2D.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/Matrix2D.cpp -o $(OUTDIR_GK_D)/Matrix2D.o
	
$(OUTDIR_GK_D)/Polygon.o : $(SRC_GRF)/Polygon.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/Polygon.cpp -o $(OUTDIR_GK_D)/Polygon.o
	
$(OUTDIR_GK_D)/Vector2D.o : $(SRC_GRF)/Vector2D.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/Vector2D.cpp -o $(OUTDIR_GK_D)/Vector2D.o
	
$(OUTDIR_GK_D)/X11Font.o : $(SRC_IMPLKIT)/X11Font.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_IMPLKIT)/X11Font.cpp -o $(OUTDIR_GK_D)/X11Font.o
	
$(OUTDIR_GK_D)/X11Image.o : $(SRC_IMPLKIT)/X11Image.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_IMPLKIT)/X11Image.cpp -o $(OUTDIR_GK_D)/X11Image.o
	
$(OUTDIR_GK_D)/X11Context.o : $(SRC_IMPLKIT)/X11Context.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_IMPLKIT)/X11Context.cpp -o $(OUTDIR_GK_D)/X11Context.o
	
$(OUTDIR_GK_D)/X11GraphicsToolkit.o : $(SRC_IMPLKIT)/X11GraphicsToolkit.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_IMPLKIT)/X11GraphicsToolkit.cpp -o $(OUTDIR_GK_D)/X11GraphicsToolkit.o
	
$(OUTDIR_GK_D)/MgcBezierCurve2.o : $(SRC_GRF)/MgcBezierCurve2.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/MgcBezierCurve2.cpp -o $(OUTDIR_GK_D)/MgcBezierCurve2.o
	
$(OUTDIR_GK_D)/MgcCurve2.o : $(SRC_GRF)/MgcCurve2.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/MgcCurve2.cpp -o $(OUTDIR_GK_D)/MgcCurve2.o
	
$(OUTDIR_GK_D)/MgcVector2.o : $(SRC_GRF)/MgcVector2.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/MgcVector2.cpp -o $(OUTDIR_GK_D)/MgcVector2.o
	
$(OUTDIR_GK_D)/MgcIntegrate.o : $(SRC_GRF)/MgcIntegrate.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/MgcIntegrate.cpp -o $(OUTDIR_GK_D)/MgcIntegrate.o
	
$(OUTDIR_GK_D)/MgcSingleCurve2.o : $(SRC_GRF)/MgcSingleCurve2.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/MgcSingleCurve2.cpp -o $(OUTDIR_GK_D)/MgcSingleCurve2.o
	
$(OUTDIR_GK_D)/MgcMath.o  : $(SRC_GRF)/MgcMath.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS_D) $(SRC_GRF)/MgcMath.cpp -o $(OUTDIR_GK_D)/MgcMath.o
	




###########################################################
#Release files
###########################################################

$(OUTDIR_GK)/GraphicsKit.o : $(SRC_GRF)/GraphicsKit.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/GraphicsKit.cpp -o $(OUTDIR_GK)/GraphicsKit.o	

$(OUTDIR_GK)/AbstractImage.o : $(SRC_GRF)/AbstractImage.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/AbstractImage.cpp -o $(OUTDIR_GK)/AbstractImage.o
	
$(OUTDIR_GK)/BasicFill.o : $(SRC_GRF)/BasicFill.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/BasicFill.cpp -o $(OUTDIR_GK)/BasicFill.o
	
$(OUTDIR_GK)/BasicStroke.o : $(SRC_GRF)/BasicStroke.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/BasicStroke.cpp -o $(OUTDIR_GK)/BasicStroke.o
	
$(OUTDIR_GK)/Color.o : $(SRC_GRF)/Color.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/Color.cpp -o $(OUTDIR_GK)/Color.o
	
$(OUTDIR_GK)/Font.o : $(SRC_GRF)/Font.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/Font.cpp -o $(OUTDIR_GK)/Font.o
	
$(OUTDIR_GK)/FontState.o : $(SRC_GRF)/FontState.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/FontState.cpp -o $(OUTDIR_GK)/FontState.o
	
$(OUTDIR_GK)/GlyphCollection.o : $(SRC_GRF)/GlyphCollection.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/GlyphCollection.cpp -o $(OUTDIR_GK)/GlyphCollection.o
	
$(OUTDIR_GK)/GraphicsContext.o : $(SRC_GRF)/GraphicsContext.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/GraphicsContext.cpp -o $(OUTDIR_GK)/GraphicsContext.o
	
$(OUTDIR_GK)/GraphicsObject.o : $(SRC_GRF)/GraphicsObject.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/GraphicsObject.cpp -o $(OUTDIR_GK)/GraphicsObject.o
	
$(OUTDIR_GK)/GraphicsToolKit.o : $(SRC_UTILS)/GraphicsToolKit.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_UTILS)/GraphicsToolKit.cpp -o $(OUTDIR_GK)/GraphicsToolKit.o
	
$(OUTDIR_GK)/ImageEvent.o : $(SRC_EVENT)/ImageEvent.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_EVENT)/ImageEvent.cpp -o $(OUTDIR_GK)/ImageEvent.o
	
$(OUTDIR_GK)/Matrix2D.o : $(SRC_GRF)/Matrix2D.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/Matrix2D.cpp -o $(OUTDIR_GK)/Matrix2D.o
	
$(OUTDIR_GK)/Polygon.o : $(SRC_GRF)/Polygon.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/Polygon.cpp -o $(OUTDIR_GK)/Polygon.o
	
$(OUTDIR_GK)/Vector2D.o : $(SRC_GRF)/Vector2D.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/Vector2D.cpp -o $(OUTDIR_GK)/Vector2D.o
	
$(OUTDIR_GK)/X11Font.o : $(SRC_IMPLKIT)/X11Font.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_IMPLKIT)/X11Font.cpp -o $(OUTDIR_GK)/X11Font.o
	
$(OUTDIR_GK)/X11Image.o : $(SRC_IMPLKIT)/X11Image.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_IMPLKIT)/X11Image.cpp -o $(OUTDIR_GK)/X11Image.o
	
$(OUTDIR_GK)/X11Context.o : $(SRC_IMPLKIT)/X11Context.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_IMPLKIT)/X11Context.cpp -o $(OUTDIR_GK)/X11Context.o
	
$(OUTDIR_GK)/X11GraphicsToolkit.o : $(SRC_IMPLKIT)/X11GraphicsToolkit.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_IMPLKIT)/X11GraphicsToolkit.cpp -o $(OUTDIR_GK)/X11GraphicsToolkit.o
	
$(OUTDIR_GK)/MgcBezierCurve2.o : $(SRC_GRF)/MgcBezierCurve2.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/MgcBezierCurve2.cpp -o $(OUTDIR_GK)/MgcBezierCurve2.o
	
$(OUTDIR_GK)/MgcCurve2.o : $(SRC_GRF)/MgcCurve2.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/MgcCurve2.cpp -o $(OUTDIR_GK)/MgcCurve2.o
	
$(OUTDIR_GK)/MgcVector2.o : $(SRC_GRF)/MgcVector2.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/MgcVector2.cpp -o $(OUTDIR_GK)/MgcVector2.o
	
$(OUTDIR_GK)/MgcIntegrate.o : $(SRC_GRF)/MgcIntegrate.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/MgcIntegrate.cpp -o $(OUTDIR_GK)/MgcIntegrate.o
	
$(OUTDIR_GK)/MgcSingleCurve2.o : $(SRC_GRF)/MgcSingleCurve2.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/MgcSingleCurve2.cpp -o $(OUTDIR_GK)/MgcSingleCurve2.o
	
$(OUTDIR_GK)/MgcMath.o  : $(SRC_GRF)/MgcMath.cpp $(GRAPHICSKIT_HDRS)
	$(CXX) $(GK_CXX_FLAGS) $(SRC_GRF)/MgcMath.cpp -o $(OUTDIR_GK)/MgcMath.o
	
	


