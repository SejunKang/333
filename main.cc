#include "G4RunManagerFactory.hh"
 #include "G4UImanager.hh"

 #include "DetectorConstruction.hh"
 #include "physics.hh"   // week7 異붽?
 #include "QBBC.hh"
 #include "ActionInitialization.hh"

 #include "G4VisExecutive.hh"
 #include "G4UIExecutive.hh"

 // week7 異붽? ?ㅻ뜑?뚯씪
 #include "QGSP_BERT.hh"
 #include "G4EmStandardPhysics.hh"
 #include "G4OpticalPhysics.hh"

 int main(int argc, char **argv)
 {
     // Detect interactive mode (if no arguments) and define UI session
     //
     G4UIExecutive *ui = nullptr;
     if (argc == 1)
         ui = new G4UIExecutive(argc, argv);

     // Set random seed number
     G4Random::setTheSeed(time(nullptr));

     // Construct the default run manager
     auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

/*	 
     // Physics list to be used (week 7)
     G4VModularPhysicsList* PL = new QGSP_BERT;
     PL -> SetVerboseLevel(0);
     PL -> ReplacePhysics(new G4EmStandardPhysics());
     G4OpticalPhysics* OP = new G4OpticalPhysics();
     PL -> RegisterPhysics(OP);
     runManager -> SetUserInitialization(PL);
*/


     // Set mandatory initialization classes
     runManager->SetUserInitialization(new DetectorConstruction());
     runManager->SetUserInitialization(new MyPhysicsList()); // week7
//   runManager->SetUserInitialization(new QBBC);
     runManager->SetUserInitialization(new ActionInitialization);

     // Initialize G4 kernel
     runManager->Initialize();

     // Initialize visualization
     auto visManager = new G4VisExecutive;
     visManager->Initialize();

     // Get the pointer to the User Interface manager
     auto UImanager = G4UImanager::GetUIpointer();
/*
         UImanager->ApplyCommand("/vis/open OGL");
         UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
         UImanager->ApplyCommand("/vis/drawVolume");
         UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
         UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
		 ui->SessionStart();
*/
		 
	// Process macro or start UI session
     if (ui)
     {
         // interactive mode
         UImanager->ApplyCommand("/control/execute vis.mac");
         ui->SessionStart();
         delete ui;
     }
     else
     {
         // batch mode
         G4String command = "/control/execute ";
         G4String filename = argv[1];
         UImanager->ApplyCommand(command + filename);
     }

     // Job termination
     // Free the store: user actions, physics_list and detector_description are
     // owned and deleted by the run manager, so they should not be deleted
     // in the main() program !
     delete visManager;
     delete runManager;

     return 0;
 }
