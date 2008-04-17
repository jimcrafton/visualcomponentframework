#include "ParticleEditor.h"
#include "ParticleRenderer.h"
#include "ParticleSystem.h"
#include "ParticleResource.h"
#include "XMLParticleResourceHandler.h"
#include "ParticleResourceManager.h"

#include <vrtoad/Math.h>

#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/DropDownControl.h"
#include "vcf/ApplicationKit/Label.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/CommandButton.h"
#include "vcf/ApplicationKit/SliderControl.h"
#include "vcf/ApplicationKit/CheckBoxControl.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"

using namespace VCF;

ParticleEditor::ParticleEditor():Window(){
	setCaption("Particle Editor");

	setWidth(640);
	setHeight(680);

	// Setup UI
	{
		MenuBar *menuBar=new MenuBar(this);
		setMenuBar(menuBar);
		MenuItem *root=menuBar->getRootMenuItem();
		CallBack* menuItemHandler=0;

		DefaultMenuItem *file=new DefaultMenuItem("&File",root,menuBar);

		DefaultMenuItem *fileLoad=new DefaultMenuItem("&Load",file,menuBar);
		menuItemHandler=new ClassProcedure1<MenuItemEvent*,ParticleEditor>(this,&ParticleEditor::onFileLoad);
		fileLoad->MenuItemClicked += menuItemHandler;

		DefaultMenuItem *fileSave=new DefaultMenuItem("&Save",file,menuBar);
		menuItemHandler=new ClassProcedure1<MenuItemEvent*,ParticleEditor>(this,&ParticleEditor::onFileSave);
		fileSave->MenuItemClicked += menuItemHandler;

		DefaultMenuItem *sep=new DefaultMenuItem("",file,menuBar);
		sep->setSeparator(true);

		DefaultMenuItem *fileExit=new DefaultMenuItem("E&xit",file,menuBar);
		menuItemHandler=new ClassProcedure1<MenuItemEvent*,ParticleEditor>(this,&ParticleEditor::onFileExit);
		fileExit->MenuItemClicked += menuItemHandler;
	}

	{
		Panel *top=new Panel();
		top->setBorder(0);

		mParticleRenderer=new ParticleRenderer();
		top->add(mParticleRenderer,AlignClient);

		mYaw=new SliderControl();
		mYaw->setDisplayOrientation(SliderControl::doHorizontal);
		mYaw->setHeight(20);
		mYaw->setTickMarkStyle(SliderControl::tmsTopLeft);
		mYaw->setTickFrequency(0);
		mYaw->setMinValue(0);
		mYaw->setMaxValue(360);
		mYaw->setPosition(mYaw->getMaxValue()/2.0f);
		mYaw->getPositionChanged().add(new ClassProcedure1<ScrollEvent*,ParticleEditor>(this,&ParticleEditor::onViewChanged));
		top->add(mYaw,AlignBottom);

		mPitch=new SliderControl();
		mPitch->setDisplayOrientation(SliderControl::doVertical);
		mPitch->setWidth(20);
		mPitch->setTickMarkStyle(SliderControl::tmsTopLeft);
		mPitch->setTickFrequency(0);
		mPitch->setMinValue(1);
		mPitch->setMaxValue(179);
		mPitch->setPosition(mPitch->getMaxValue()/2.0f);
		mPitch->getPositionChanged().add(new ClassProcedure1<ScrollEvent*,ParticleEditor>(this,&ParticleEditor::onViewChanged));
		top->add(mPitch,AlignRight);

		mZoom=new SliderControl();
		mZoom->setDisplayOrientation(SliderControl::doVertical);
		mZoom->setWidth(20);
		mZoom->setTickMarkStyle(SliderControl::tmsBottomRight);
		mZoom->setTickFrequency(0);
		mZoom->setMinValue(1);
		mZoom->setMaxValue(100);
		mZoom->setPosition(mZoom->getMaxValue()/2.0f);
		mZoom->getPositionChanged().add(new ClassProcedure1<ScrollEvent*,ParticleEditor>(this,&ParticleEditor::onViewChanged));
		top->add(mZoom,AlignLeft);

		add(top,AlignClient);

		// Update the view
		ScrollEvent e(this,0);
		onViewChanged(&e);
	}

	Panel *bottom=new Panel();
	bottom->setBorder(0);	;
	bottom->setHeight(180);
	add(bottom,AlignBottom);

	HorizontalLayoutContainer *bottomContainer = new HorizontalLayoutContainer();
	bottomContainer->setNumberOfColumns(3);
	bottomContainer->setColumnWidth( 0, 200 );
	bottomContainer->setColumnWidth( 1, 200 );
	bottomContainer->setColumnWidth( 2, 200 );
	bottomContainer->setColumnTweenWidth( 0, 20 );
	bottomContainer->setColumnTweenWidth( 1, 20 );
	bottomContainer->setMaximizeLastRow(true);
	bottom->setContainer( bottomContainer );

	Panel *bottomLeft=new Panel();
	bottomLeft->setBorder(0);	

	Panel *bottomCenter=new Panel();
	bottomCenter->setBorder(0);	

	Panel *bottomRight=new Panel();
	bottomRight->setBorder(0);	

	bottom->add(bottomLeft,AlignLeft);
	bottom->add(bottomCenter,AlignLeft);
	bottom->add(bottomRight,AlignClient);

	
	double ctrlHeight = 22;
	double ctrlSpace = 6;
	
	{
		Panel *gradualStartPanel=new Panel();
		gradualStartPanel->setBorder(0);

		CommandButton *reset=new CommandButton();
		reset->setCaption("Reset sim");
		reset->setWidth(60);
		reset->getButtonClicked().add(new ClassProcedure1<ButtonEvent*,ParticleEditor>(this,&ParticleEditor::onReset));
		gradualStartPanel->add(reset,AlignLeft);

		mGradualStart=new CheckBoxControl();
		mGradualStart->setCaption(":Gradual start");
		mGradualStart->setWidth(100);
		mGradualStart->getButtonClicked().add(new ClassProcedure1<ButtonEvent*,ParticleEditor>(this,&ParticleEditor::onGradualStart));
		gradualStartPanel->add(mGradualStart,AlignRight);

		gradualStartPanel->setBounds(0,0,200,ctrlHeight);

		bottomLeft->add(gradualStartPanel);
	}

	{
		Panel *numParticlePanel=new Panel();
		numParticlePanel->setBorder(0);

		Label *label=new Label();
		label->setCaption("Num Particles:");
		label->setWidth(80);
		numParticlePanel->add(label,AlignLeft);

		mNumParticles=new Spinner();
		mNumParticles->setMin(0);
		mNumParticles->setMax(30000);
		mNumParticles->setIncrement(10);
		mNumParticles->setValue(10);
		mNumParticles->getSpinnerChanged().add(new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onNumParticles));
		numParticlePanel->add(mNumParticles,AlignClient);

		numParticlePanel->setBounds(0, 1*ctrlHeight + 1*ctrlSpace ,200,ctrlHeight);

		bottomLeft->add(numParticlePanel);
	}

	{
		Panel *systemLifePanel=new Panel();
		systemLifePanel->setBorder(0);

		Label *label=new Label();
		label->setCaption("System life (sec):");
		label->setWidth(80);
		systemLifePanel->add(label,AlignLeft);

		mSystemLife=new Spinner();
		mSystemLife->setInteger(false);
		mSystemLife->setMin(0);
		mSystemLife->setMax(10000);
		mSystemLife->setIncrement(0.1f);
		mSystemLife->getSpinnerChanged().add(new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onSystemLife));
		systemLifePanel->add(mSystemLife,AlignClient);

		systemLifePanel->setBounds(0,2*ctrlHeight + 2*ctrlSpace,200,ctrlHeight);

		bottomLeft->add(systemLifePanel);
	}

	{
		Panel *partLifePanel=new Panel();

		partLifePanel->setBorder(0);

		Label *label=new Label();
		label->setCaption("Particle life (sec):");
		label->setWidth(80);
		partLifePanel->add(label,AlignLeft);

		mPartLife=new Spinner();
		mPartLife->setInteger(false);
		mPartLife->setMin(0);
		mPartLife->setMax(10000);
		mPartLife->setIncrement(0.1f);
		mPartLife->getSpinnerChanged().add(new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onParticleLife));
		partLifePanel->add(mPartLife,AlignClient);

		partLifePanel->setBounds(0,3*ctrlHeight + 3*ctrlSpace,200,ctrlHeight);

		bottomLeft->add(partLifePanel);
	}

	{
		Panel *speedPanel=new Panel();
		speedPanel->setBorder(0);

		Label *label=new Label();
		label->setCaption("Initial speed:");
		label->setWidth(60);
		speedPanel->add(label,AlignLeft);

		mInitialSpeed=new TextControl();
		mInitialSpeed->getTextModel()->ModelChanged += new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onInitialSpeed);
		mInitialSpeed->setWidth(40);
		speedPanel->add(mInitialSpeed,AlignLeft);

		label=new Label();
		label->setCaption("   Variance:");
		label->setWidth(60);
		speedPanel->add(label,AlignLeft);

		mInitialVariance=new TextControl();
		mInitialVariance->getTextModel()->ModelChanged += new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onInitialVariance);
		speedPanel->add(mInitialVariance,AlignClient);

		speedPanel->setBounds(0,4*ctrlHeight + 4*ctrlSpace,200,ctrlHeight);

		bottomLeft->add(speedPanel);
	}

	{
		Panel *gravityPanel=new Panel();
		gravityPanel->setBorder(0);

		Label *label=new Label();
		label->setCaption("   Gravity:");
		label->setWidth(60);
		gravityPanel->add(label,AlignLeft);

		mGravity=new TextControl();
		mGravity->getTextModel()->ModelChanged += new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onGravity);
		mGravity->setWidth(40);
		gravityPanel->add(mGravity,AlignLeft);

		label=new Label();
		label->setCaption("   Variance:");
		label->setWidth(60);
		gravityPanel->add(label,AlignLeft);

		mGravityVariance=new TextControl();
		mGravityVariance->getTextModel()->ModelChanged += new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onGravityVariance);
		gravityPanel->add(mGravityVariance,AlignClient);

		gravityPanel->setBounds(0,5*ctrlHeight + 5*ctrlSpace,200,ctrlHeight);

		bottomLeft->add(gravityPanel);
	}

	{
		Panel *typePanel=new Panel();
		typePanel->setBorder(0);

		Label *label=new Label();
		label->setCaption("Primitive:");
		label->setWidth(70);
		typePanel->add(label,AlignLeft);

		mParticleType=new DropDownControl();
		mParticleType->addItem("Points");
		mParticleType->addItem("Lines");
		mParticleType->addItem("Tris");
		mParticleType->addItem("Quads");
		mParticleType->ItemSelectionChanged.add(new ClassProcedure1<ItemEvent*,ParticleEditor>(this,&ParticleEditor::onParticleType));
		typePanel->add(mParticleType,AlignClient);

		typePanel->setBounds(0,0,200,ctrlHeight);
		bottomCenter->add(typePanel);
	}

	{
		Panel *alignmentPanel=new Panel();
		alignmentPanel->setBorder(0);

		Label *l=new Label();
		l->setCaption("Alignment:");
		l->setWidth(70);
		alignmentPanel->add(l,AlignLeft);

		mAlignment=new DropDownControl();
		mAlignment->addItem("View");
		mAlignment->addItem("Velocity");
		mAlignment->ItemSelectionChanged.add(new ClassProcedure1<ItemEvent*,ParticleEditor>(this,&ParticleEditor::onAlignment));
		alignmentPanel->add(mAlignment,AlignClient);

		alignmentPanel->setBounds(0,1*ctrlHeight + 1*ctrlSpace,200,ctrlHeight);
		bottomCenter->add(alignmentPanel);
	}

	{
		Panel *blendPanel=new Panel();
		blendPanel->setBorder(0);

		Label *l=new Label();
		l->setCaption("Blending:");
		l->setWidth(70);
		blendPanel->add(l,AlignLeft);

		mBlending=new DropDownControl();
		mBlending->addItem("None");
		mBlending->addItem("Color");
		mBlending->addItem("Color Additive");
		mBlending->addItem("Alpha");
		mBlending->addItem("Alpha Additive");
		mBlending->ItemSelectionChanged.add(new ClassProcedure1<ItemEvent*,ParticleEditor>(this,&ParticleEditor::onBlending));
		mBlending->setWidth( 100 );
		blendPanel->add(mBlending,AlignClient);

		blendPanel->setBounds(0,2*ctrlHeight + 2*ctrlSpace,200,ctrlHeight);
		bottomCenter->add(blendPanel);
	}

	{
		Panel *depthTestPanel=new Panel();
		depthTestPanel->setBorder(0);

		mDepthTest=new CheckBoxControl();
		mDepthTest->setCaption(":Enable Depth Testing");
		mDepthTest->getButtonClicked().add(new ClassProcedure1<ButtonEvent*,ParticleEditor>(this,&ParticleEditor::onDepthTest));
		depthTestPanel->add(mDepthTest,AlignClient);

		depthTestPanel->setBounds(0,3*ctrlHeight + 3*ctrlSpace,200,ctrlHeight);
		bottomCenter->add(depthTestPanel);
	}

	{
		Panel *colorPanel=new Panel();
		colorPanel->setBorder(0);

		Panel *p=new Panel();
		p->setBorder(0);

		Label *l=new Label();
		l->setCaption("Start Color :");
		l->setWidth(70);
		p->add(l,AlignLeft);

		mStartColor=new ColorPicker();
		mStartColor->getColorChanged().add(new ClassProcedure1<ButtonEvent*,ParticleEditor>(this,&ParticleEditor::onStartColor));
		p->add(mStartColor,AlignClient);

		p->setHeight(ctrlHeight);

		colorPanel->add(p,AlignTop);

		p=new Panel();
		p->setBorder(0);

		l=new Label();
		l->setCaption("End Color :");
		l->setWidth(70);
		p->add(l,AlignLeft);

		mEndColor=new ColorPicker();
		mEndColor->getColorChanged().add(new ClassProcedure1<ButtonEvent*,ParticleEditor>(this,&ParticleEditor::onEndColor));
		p->add(mEndColor,AlignClient);

		p->setHeight(ctrlHeight);

		colorPanel->add(p,AlignBottom);

		colorPanel->setBounds(0,4*ctrlHeight + 4*ctrlSpace,200,ctrlHeight*2);
		bottomCenter->add(colorPanel);
	}


	{
		Panel *trailingPanel=new Panel();
		trailingPanel->setBorder(0);

		Label *l=new Label();
		l->setCaption("Trailing system:");
		l->setWidth(80);
		trailingPanel->add(l,AlignLeft);

		mTrailingSystem=new TextControl();
		mTrailingSystem->getTextModel()->ModelChanged += new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onTrailingSystem);
		trailingPanel->add(mTrailingSystem,AlignClient);

		trailingPanel->setBounds(0,0,210,ctrlHeight);
		bottomRight->add(trailingPanel);
	}

	{
		Panel *endingPanel=new Panel();
		endingPanel->setBorder(0);

		Label *l=new Label();
		l->setCaption("Ending system:");
		l->setWidth(80);
		endingPanel->add(l,AlignLeft);

		mEndingSystem=new TextControl();
		mEndingSystem->getTextModel()->ModelChanged += new ClassProcedure1<TextEvent*,ParticleEditor>(this,&ParticleEditor::onEndingSystem);
		endingPanel->add(mEndingSystem,AlignClient);

		endingPanel->setBounds(0,ctrlHeight+ctrlSpace,210,ctrlHeight);
		bottomRight->add(endingPanel);
	}

	{
		mTexturePanel=new Panel();
		mTexturePanel->setBorder(0);

		CommandButton *newTexture=new CommandButton();
		newTexture->setCaption("New Tex");
		newTexture->setWidth(50);
		newTexture->getButtonClicked().add(new ClassProcedure1<ButtonEvent*,ParticleEditor>(this,&ParticleEditor::onNewTexture));
		mTexturePanel->add(newTexture,AlignLeft);

		CommandButton *deleteTexture=new CommandButton();
		deleteTexture->setCaption("Delete");
		deleteTexture->setWidth(50);
		deleteTexture->getButtonClicked().add(new ClassProcedure1<ButtonEvent*,ParticleEditor>(this,&ParticleEditor::onDeleteTexture));
		mTexturePanel->add(deleteTexture,AlignRight);

		mTextureList=new DropDownControl();
		mTexturePanel->add(mTextureList,AlignClient);

		mTexturePanel->setBounds(0,40,210,20);
		// Textures not functional yet :(
//		bottomRight->add(mTexturePanel);

		mTexturePanel->setVisible(false);
	}



	// Setup particle system components
	mParticleSystem=new ParticleSystem();
	mParticleRenderer->setParticleSystem(mParticleSystem);
	mParticleResource=new ParticleResource();
	setParticleResource(mParticleResource);
}

void ParticleEditor::onViewChanged(ScrollEvent *e){
	float yaw=mYaw->getPosition();
	float pitch=90-mPitch->getPosition();
	float zoom=mZoom->getPosition();

	vrtoad::Vector3 offset=vrtoad::Vector3(0,-1,0);

	offset=vrtoad::makeMatrix3x3FromX(vrtoad::toRad(pitch))*offset;
	offset=vrtoad::makeMatrix3x3FromZ(vrtoad::toRad(yaw))*offset;

	offset*=zoom;

	mParticleRenderer->setViewPoint(offset);
}

void ParticleEditor::onNumParticles(TextEvent *e){
	mParticleResource->setAmount(mNumParticles->getValue());
}

void ParticleEditor::onReset(ButtonEvent *e){
	mParticleSystem->reset();
}

void ParticleEditor::onGradualStart(ButtonEvent *e){
	mParticleResource->setGradualStart(mGradualStart->isChecked());
}

void ParticleEditor::onParticleLife(TextEvent *e){
	mParticleResource->setParticleLife(mPartLife->getValue());
}

void ParticleEditor::onSystemLife(TextEvent *e){
	mParticleResource->setSystemLife(mSystemLife->getValue());
}

void ParticleEditor::onInitialSpeed(TextEvent *e){
	float value=0;
	try{
		value=StringUtils::fromStringAsFloat(mInitialSpeed->getTextModel()->getText());
	}
	catch(std::exception&){
		value=0;
	}

	mParticleResource->setInitialSpeed(value);	
}

void ParticleEditor::onInitialVariance(TextEvent *e){
	float value=0;
	try{
		value=StringUtils::fromStringAsFloat(mInitialVariance->getTextModel()->getText());
	}
	catch(std::exception&){
		value=0;
	}

	mParticleResource->setInitialVariance(value);
}

void ParticleEditor::onGravity(TextEvent *e){
	float value=0;
	try{
		value=StringUtils::fromStringAsFloat(mGravity->getTextModel()->getText());
	}
	catch(std::exception&){
		value=0;
	}

	mParticleResource->setGravity(value);
}

void ParticleEditor::onGravityVariance(TextEvent *e){
	float value=0;
	try{
		value=StringUtils::fromStringAsFloat(mGravityVariance->getTextModel()->getText());
	}
	catch(std::exception&){
		value=0;
	}

	mParticleResource->setGravityVariance(value);
}

void ParticleEditor::onParticleType(ItemEvent *e){
	uint32 index = mParticleType->getSelectedItem();

	if(index != ListModel::InvalidIndex){
		String itemVal = mParticleType->getListModel()->getAsString(index);

		if( itemVal =="Points"){
			mParticleResource->setType(ParticleResource::TYPE_POINTS);
			mTexturePanel->setVisible(false);
		}
		else if(itemVal=="Lines"){
			mParticleResource->setType(ParticleResource::TYPE_LINES);
			mTexturePanel->setVisible(false);
		}
		else if(itemVal=="Tris"){
			mParticleResource->setType(ParticleResource::TYPE_TRIANGLES);
			mTexturePanel->setVisible(false);
		}
		else if(itemVal=="Quads"){
			mParticleResource->setType(ParticleResource::TYPE_QUADS);
			mTexturePanel->setVisible(true);
		}
	}
}

void ParticleEditor::onAlignment(ItemEvent *e){
	
	uint32 index = mAlignment->getSelectedItem();
	String itemVal = mAlignment->getListModel()->getAsString(index);
	
	if(itemVal=="View"){
		mParticleResource->setAlignment(ParticleResource::ALIGN_VIEW);
	}
	else if(itemVal=="Velocity"){
		mParticleResource->setAlignment(ParticleResource::ALIGN_VELOCITY);
	}
	
}

void ParticleEditor::onBlending(ItemEvent *e){
	uint32 index = mBlending->getSelectedItem();
	String itemVal = mBlending->getListModel()->getAsString(index);
	
	if(itemVal=="None"){
		mParticleResource->setBlending(ParticleResource::BLEND_NONE);
	}
	else if(itemVal=="Color"){
		mParticleResource->setBlending(ParticleResource::BLEND_COLOR);
	}
	else if(itemVal=="Color Additive"){
		mParticleResource->setBlending(ParticleResource::BLEND_COLOR_ADDITIVE);
	}
	else if(itemVal=="Alpha"){
		mParticleResource->setBlending(ParticleResource::BLEND_ALPHA);
	}
	else if(itemVal=="Alpha Additive"){
		mParticleResource->setBlending(ParticleResource::BLEND_ALPHA_ADDITIVE);
	}
	
}

void ParticleEditor::onDepthTest(ButtonEvent *e){
	mParticleResource->mDepthTest=mDepthTest->isChecked();
}

void ParticleEditor::onStartColor(ButtonEvent *e){
	vrtoad::Vector4 cv;
	Color *cc=mStartColor->getColor();

	cv[0]=cc->getRed();
	cv[1]=cc->getGreen();
	cv[2]=cc->getBlue();
	cv[3]=mStartColor->getAlpha();

	mParticleResource->setStartColor(cv);
}

void ParticleEditor::onEndColor(ButtonEvent *e){
	vrtoad::Vector4 cv;
	Color *cc=mEndColor->getColor();

	cv[0]=cc->getRed();
	cv[1]=cc->getGreen();
	cv[2]=cc->getBlue();
	cv[3]=mEndColor->getAlpha();

	mParticleResource->setEndColor(cv);
}

void ParticleEditor::onTrailingSystem(TextEvent *e){
	mParticleResource->mTrailingSystem=mTrailingSystem->getTextModel()->getText();
}

void ParticleEditor::onEndingSystem(TextEvent *e){
	mParticleResource->mEndingSystem=mEndingSystem->getTextModel()->getText();
}

void ParticleEditor::onNewTexture(ButtonEvent *e){
	CommonFileOpenDialog *dialog=new CommonFileOpenDialog();
	FilePath path(Application::getRunningInstance()->getFileName());
	dialog->setDirectory(path.getPathName());
	dialog->addFilter("Bitmaps (*.bmp)","*.bmp");
	dialog->setSelectedFilter("*.bmp");
	dialog->setFileMustExist(true);
	dialog->setFileName("*.bmp");
	
	if(dialog->execute()){
		if(strstr(dialog->getFileName().ansi_c_str(),".bmp")==0){
			Dialog::showMessage("Error: File must end with .bmp");
		}
		else{
			// TODO: Filter out the base path from the file name;
			FilePath file=dialog->getFileName();

			mTextureList->addItem(file);
			mParticleResource->mTextures.push_back(file.getFileName());
		}
	}
}

void ParticleEditor::onDeleteTexture(ButtonEvent *e){
	uint32 index = mTextureList->getSelectedItem();
	

	if(index != ListModel::InvalidIndex){
		mTextureList->selectItem(ListModel::InvalidIndex);
		mTextureList->getListModel()->remove(index);

		mParticleResource->mTextures.clear();

		int i;
		for(i=0;i<mTextureList->getListModel()->getCount();i++){
			String itemVal = mTextureList->getListModel()->getAsString(i);
			mParticleResource->mTextures.push_back(itemVal);
		}
	}
}

void ParticleEditor::onFileLoad(MenuItemEvent *e){
	CommonFileOpenDialog *dialog=new CommonFileOpenDialog();
	FilePath path(Application::getRunningInstance()->getFileName());
	dialog->setDirectory(path.getPathName());
	dialog->addFilter("Particle XML Files (*.xml)","*.xml");
	dialog->setSelectedFilter("*.xml");
	dialog->setFileMustExist(true);
	dialog->setFileName("*.xml");
	
	if(dialog->execute()){
		FileInputStream *in=0;
		try{
			in=new FileInputStream(dialog->getFileName());
		}
		catch(std::exception&){
		}

		if(in){
			XMLParticleResourceHandler handler;
			ParticleResource *res=handler.loadResource(in);

			if(res){
				FilePath p(dialog->getFileName());
				res->mName=p.getBaseName(true);

				ParticleSystem *oldsys=mParticleSystem;
				mParticleSystem=new ParticleSystem();
				mParticleRenderer->setParticleSystem(mParticleSystem);
				setParticleResource(res);
				delete oldsys;

				ParticleResourceManager::reset();
			}

			delete in;
		}
	}
}

void ParticleEditor::onFileSave(MenuItemEvent *e){
	CommonFileOpenDialog *dialog=new CommonFileOpenDialog();
	FilePath path(Application::getRunningInstance()->getFileName());
	dialog->setDirectory(path.getPathName());
	dialog->addFilter("Particle XML Files (*.xml)","*.xml");
	dialog->setSelectedFilter("*.xml");
	dialog->setFileMustExist(false);
	dialog->setFileName("*.xml");
	
	if(dialog->execute()){
		FileOutputStream *out=new FileOutputStream(dialog->getFileName());

		XMLParticleResourceHandler handler;
		handler.saveResource(mParticleResource,out);

		delete out;
	}
}

void ParticleEditor::setParticleResource(ParticleResource *r){
	mParticleSystem->setParticleResource(r);
	mParticleResource=r;

	// Setup defaults
	mGradualStart->setChecked(r->getGradualStart());
	mNumParticles->setValue(r->getAmount());
	mPartLife->setValue(r->getParticleLife());
	mSystemLife->setValue(r->getSystemLife());
	mInitialSpeed->getTextModel()->setText(StringUtils::toString(r->getInitialSpeed()));
	mInitialVariance->getTextModel()->setText(StringUtils::toString(r->getInitialVariance()));
	mGravity->getTextModel()->setText(StringUtils::toString(r->getGravity()));
	mGravityVariance->getTextModel()->setText(StringUtils::toString(r->getGravityVariance()));

	mParticleType->selectItem(r->getType());
	mAlignment->selectItem(r->getAlignment());
	mBlending->selectItem(r->getBlending());
	mDepthTest->setChecked(r->mDepthTest);

	mStartColor->setColor(new Color(r->getStartColor()[0],r->getStartColor()[1],r->getStartColor()[2]),r->getStartColor()[3]);
	mEndColor->setColor(new Color(r->getEndColor()[0],r->getEndColor()[1],r->getEndColor()[2]),r->getEndColor()[3]);

	mTrailingSystem->getTextModel()->setText(r->mTrailingSystem);
	mEndingSystem->getTextModel()->setText(r->mEndingSystem);

	mParticleSystem->reset();
}

void ParticleEditor::onFileExit(MenuItemEvent *e){
	close();
}

/**
$Id$
*/
