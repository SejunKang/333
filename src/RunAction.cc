//#include "G4RunManager.hh"

#include <ctime>
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4RootAnalysisManager.hh"
#include "RunAction.hh"

RunAction::RunAction(): G4UserRunAction()
{
	
	auto AM = G4RootAnalysisManager::Instance();

	AM -> SetVerboseLevel(0);

	AM -> CreateNtuple("mCP", "mCP");
	AM -> CreateNtupleIColumn("eventID"); // Column ID = 0
	AM -> CreateNtupleDColumn("energy" ); // Column ID = 1
	AM -> FinishNtuple();
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run *)
{

	auto AM = G4RootAnalysisManager::Instance();
/*
	time_t rawTime;
	struct tm* timeInfo;
	char buffer[80];
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%s", timeInfo);
	std::string sTime(buffer);

	G4String fileName = "mCP_";
	fileName += sTime;
	fileName += ".root";
	G4cout << fileName << G4endl;

	AM -> OpenFile(fileName);
	G4cout << "Using" << AM -> GetType() << G4endl;
*/
	AM -> OpenFile("output.root");
}

void RunAction::EndOfRunAction(const G4Run *)
{

	auto AM = G4RootAnalysisManager::Instance();

	AM -> Write();

	AM -> CloseFile();

}
