#include "StateMachine.h"
#include "State.h"
using namespace std;
using namespace cv;


States StateMachine::sCurrentState = States::BOOTING;


/*Constructor*/
#ifdef DIRECTORY_INPUT    // ^TODO: Define Seprate Constructor for camera input which takes SDI object.
StateMachine::StateMachine(const vector<cv::String>& filenames) 
: 
  mFiles(filenames)

{
	#ifdef PROFILER_ENABLED
	const std::string str = filenames[0];
	LOG_INFO_(LDTLog::STATE_MACHINE_LOG) <<endl
										 <<"******************************"<<endl
										 <<  "DIRECTORY_INPUT DEFINED." <<endl <<str<<endl
										 <<"******************************"<<endl<<endl;	
										 #endif
	
	
	#ifdef PROFILER_ENABLED
	LOG_INFO_(LDTLog::STATE_MACHINE_LOG) <<endl
										 <<"******************************"<<endl
										 <<  "StateMachine Constructed" <<endl
										 <<"******************************"<<endl<<endl;	
										#endif						
}


#else

StateMachine::StateMachine()
: 
	mStateStrings({ "BOOTING", "BUFFERING", "DETECTING_LANES", "RESETING" })

{

	#ifdef PROFILER_ENABLED
	LOG_INFO_(LDTLog::STATE_MACHINE_LOG) <<endl
										 <<"******************************"<<endl
										 <<  "StateMachine Constructed."   <<endl
										 <<"******************************"<<endl<<endl;	
										 #endif										
}

#endif


int StateMachine::spin(shared_ptr<SigInit> sigInit)
{


	// Preparing the spin process 
	
	Camera	camera;
	Lane    lane;
	
	unique_ptr<LaneFilter>  		laneFilter;
	unique_ptr<VanishingPtFilter>   vanishingPtFilter;
	unique_ptr<Templates> 			templates;
	
	
	
	// Life Scope of Buffering Process
	{
		unique_ptr<BufferingState>  bufferingState(new BufferingState());
			
	
			// Life Scope of Booting Process
			{
				
					unique_ptr<InitState> 		bootingState(new InitState());
				
					/*******************************************/
								// INITIALISING //
		
					laneFilter 			= bootingState->createLaneFilter();
					vanishingPtFilter	= bootingState->createVanishingPtFilter();
					templates           = bootingState->createTemplates();
					
					/*******************************************/
								  //TRANSITION//
			
					if (bootingState->currentStatus == StateStatus::DONE)
					{  
						
						sCurrentState =	States::BUFFERING;	
													
							/*Inject Dependencies for Buffering State */
								  
							#ifdef DIRECTORY_INPUT 
								bufferingState->setSource(mFiles);
							#else
								bufferingState->setSource();
							#endif
									
							bufferingState->setTemplates(templates.get());																				
					}
					
					else 
					{
						sCurrentState = States::DISPOSING;
						
							#ifdef PROFILER_ENABLED
							LOG_INFO_(LDTLog::STATE_MACHINE_LOG) <<endl
										 <<"******************************"<<endl
										 <<  "Could not Boot Properly, Shutting Down the State-Machine..."   <<endl
										 <<"******************************"<<endl<<endl;
							#endif
					}
					

							
			} //bootingState is out of scope from here onwards
	
	
	
			while (bufferingState->currentStatus == StateStatus::ACTIVE)
			{
				
				bufferingState->run();
			
				if (sigInit->sStatus==SigStatus::STOP)
				return -1;				
			}
			
			
			if( bufferingState->currentStatus == StateStatus::DONE)
			{
				// ^TODO: Move the complete buffering state as superclass of Lane Tracking State.
				// Inherit Buffering State into Lane Tracking State 
				sCurrentState = States::DETECTING_LANES;				
			}
			
			else
			{
				sCurrentState = States::DISPOSING;
			
						#ifdef PROFILER_ENABLED
						LOG_INFO_(LDTLog::STATE_MACHINE_LOG) <<endl
							<<"******************************"<<endl
							<<  "Could not complete Buffering Process, Shutting Down the State-Machine..." <<endl
							<<"******************************"<<endl<<endl;		
						#endif
			}
		   

	} // bufferingState is out of scope from here onwards
	
								  
	
	return 0;
}







StateMachine::~StateMachine()
{
	
}

