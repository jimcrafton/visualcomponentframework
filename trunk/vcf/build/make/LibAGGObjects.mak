###########################################################
#
#CVS Log info
#$Log$
#Revision 1.2  2003/12/18 05:15:47  ddiego
#merge from devmain-0-6-2 branch into the stable branch
#
#Revision 1.1.2.1  2003/10/03 01:07:48  ddiego
#added/fixed problems to get it to compile under linux
#

SRC_AGG = ../../thirdparty/common/agg/src
AGG_CX_FLAGS_D=$(GK_CXX_FLAGS_D) -I../../thirdparty/common/agg/include

$(OUTDIR_GK_D)/agg_affine_matrix.o : $(SRC_AGG)/agg_affine_matrix.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_affine_matrix.cpp -o $(OUTDIR_GK_D)/agg_affine_matrix.o
	
$(OUTDIR_GK_D)/agg_bspline.o : $(SRC_AGG)/agg_bspline.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_bspline.cpp -o $(OUTDIR_GK_D)/agg_bspline.o	

$(OUTDIR_GK_D)/agg_curves.o : $(SRC_AGG)/agg_curves.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_curves.cpp -o $(OUTDIR_GK_D)/agg_curves.o	
	
$(OUTDIR_GK_D)/agg_gen_stroke.o : $(SRC_AGG)/agg_gen_stroke.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_gen_stroke.cpp -o $(OUTDIR_GK_D)/agg_gen_stroke.o	

$(OUTDIR_GK_D)/agg_gsv_text.o : $(SRC_AGG)/agg_gsv_text.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_gsv_text.cpp -o $(OUTDIR_GK_D)/agg_gsv_text.o	
	
$(OUTDIR_GK_D)/agg_path_storage.o : $(SRC_AGG)/agg_path_storage.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_path_storage.cpp -o $(OUTDIR_GK_D)/agg_path_storage.o		
	
$(OUTDIR_GK_D)/agg_rasterizer_scanline_aa.o : $(SRC_AGG)/agg_rasterizer_scanline_aa.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_rasterizer_scanline_aa.cpp -o $(OUTDIR_GK_D)/agg_rasterizer_scanline_aa.o		

$(OUTDIR_GK_D)/agg_scanline_u8.o : $(SRC_AGG)/agg_scanline_u8.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_scanline_u8.cpp -o $(OUTDIR_GK_D)/agg_scanline_u8.o		
	


AGG_CX_FLAGS=$(GK_CXX_FLAGS) -I../../thirdparty/common/agg/include

$(OUTDIR_GK)/agg_affine_matrix.o : $(SRC_AGG)/agg_affine_matrix.cpp 
	$(CXX) $(AGG_CX_FLAGS) $(SRC_AGG)/agg_affine_matrix.cpp -o $(OUTDIR_GK)/agg_affine_matrix.o
	
$(OUTDIR_GK)/agg_bspline.o : $(SRC_AGG)/agg_bspline.cpp 
	$(CXX) $(AGG_CX_FLAGS) $(SRC_AGG)/agg_bspline.cpp -o $(OUTDIR_GK)/agg_bspline.o	

$(OUTDIR_GK)/agg_curves.o : $(SRC_AGG)/agg_curves.cpp 
	$(CXX) $(AGG_CX_FLAGS_D) $(SRC_AGG)/agg_curves.cpp -o $(OUTDIR_GK)/agg_curves.o	
	
$(OUTDIR_GK)/agg_gen_stroke.o : $(SRC_AGG)/agg_gen_stroke.cpp 
	$(CXX) $(AGG_CX_FLAGS) $(SRC_AGG)/agg_gen_stroke.cpp -o $(OUTDIR_GK)/agg_gen_stroke.o	

$(OUTDIR_GK)/agg_gsv_text.o : $(SRC_AGG)/agg_gsv_text.cpp 
	$(CXX) $(AGG_CX_FLAGS) $(SRC_AGG)/agg_gsv_text.cpp -o $(OUTDIR_GK)/agg_gsv_text.o	
	
$(OUTDIR_GK)/agg_path_storage.o : $(SRC_AGG)/agg_path_storage.cpp 
	$(CXX) $(AGG_CX_FLAGS) $(SRC_AGG)/agg_path_storage.cpp -o $(OUTDIR_GK)/agg_path_storage.o		
	
$(OUTDIR_GK)/agg_rasterizer_scanline_aa.o : $(SRC_AGG)/agg_rasterizer_scanline_aa.cpp 
	$(CXX) $(AGG_CX_FLAGS) $(SRC_AGG)/agg_rasterizer_scanline_aa.cpp -o $(OUTDIR_GK)/agg_rasterizer_scanline_aa.o		

$(OUTDIR_GK)/agg_scanline_u8.o : $(SRC_AGG)/agg_scanline_u8.cpp 
	$(CXX) $(AGG_CX_FLAGS) $(SRC_AGG)/agg_scanline_u8.cpp -o $(OUTDIR_GK)/agg_scanline_u8.o	


	
