#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UnionSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4EllipticalCone.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "DetectorConstruction.hh"


#include "G4MultiFunctionalDetector.hh"
#include "G4PSNofCollision.hh"
#include "G4PSPopulation.hh"
#include "G4SDParticleFilter.hh"


DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();

	auto matPlastic = nist -> FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");


//===== Optical Properties ====================================
	G4double energy[2] = {1.239841939*eV/0.9,1.239841939*eV/0.2};
	G4double rindexmatPlastic[2] = {1.1, 1.3};
	G4double rindexWorld[2] = {1.0,1.0};

	G4double reflectivity[2] = { 0.2, 0.5 };

//===== Scintillator Properties ===============================

	G4MaterialPropertiesTable *mptmatPlastic = new G4MaterialPropertiesTable();
	mptmatPlastic->AddProperty("RINDEX", energy, rindexmatPlastic, 2);


	G4double scint[2] =  {0.1,1.0};

	//  mptmatPlastic -> AddProperty("EFFICIENCY", energy, efficiency);
	
	//  mptmatPlastic -> AddProperty("ABSLENGTH", energy, absorption);

	mptmatPlastic -> AddProperty("SCINTILLATIONCOMPONENT1", energy, scint,2);
	mptmatPlastic -> AddProperty("SCINTILLATIONCOMPONENT2", energy, scint,2);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONYIELD", 0.5/MeV);
	mptmatPlastic -> AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20. *ns);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONTIMECONSTANT2", 45. *ns);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONYIELD", 1.0);
	mptmatPlastic -> AddConstProperty("SCINTILLATIONYIELD2", 0.0);

	matPlastic->SetMaterialPropertiesTable(mptmatPlastic);

//=====================================================
//===== World Properties ========================================
	G4Material *WorldMat = nist -> FindOrBuildMaterial("G4_AIR");

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld -> AddProperty("RINDEX", energy, rindexWorld,2);
	mptWorld -> AddProperty("REFLECTIVITY", energy, reflectivity, 2);

	WorldMat -> SetMaterialPropertiesTable(mptWorld);

// === World ======================================================
	auto WorldSize = 4.0 *m;
	G4Box *SolidWorld = new G4Box("SolidWorld", 0.5*WorldSize, 0.5*WorldSize, 0.5*WorldSize);
	G4LogicalVolume *WorldLV = new G4LogicalVolume(SolidWorld, WorldMat, "LogicalWorld");

	G4VPhysicalVolume *WorldPV = new G4PVPlacement(0, G4ThreeVector(), WorldLV, "PhysisWorld",0,false,0,true);


 // Cylinder ============================================
     Cylsize = 5. * cm;
     CylDiameter = 50.* cm;
     CylHeight = 100. * cm;

     auto CylPos = G4ThreeVector(0.,0.,0. *cm);
     CylSol = new G4Tubs("Cylinder", 0., .5 * CylDiameter, .5 * CylHeight, 0., 360. *deg);

     CylLV = new G4LogicalVolume(CylSol, matPlastic, "Cylinder");

 // Elliptical Cone ============================================
     auto ConePos = G4ThreeVector(0.,0.,100.*cm);
     G4EllipticalCone* ConeSol = new G4EllipticalCone("Cone", 0.225,0.225,61.11*cm, 50*cm);

     ConeLV = new G4LogicalVolume(ConeSol, matPlastic, "Cone");

 // Scintillator ==================================================
     SciSol = new G4UnionSolid("Scisol", CylSol, ConeSol, 0, G4ThreeVector(ConePos));
     SciLV = new G4LogicalVolume(SciSol, matPlastic, "Scintillator");
     SciPV = new G4PVPlacement(0,G4ThreeVector(), SciLV, "Scintillator", WorldLV, false,0);


// PMT ============================================
	 PMTDiameter = 10. * cm; 
	 PMTHeight = 5. * cm;

	 auto PMTPos = G4ThreeVector(0., 0., PMTHeight/2 + 150. *cm);
 	 PMTSol = new G4Tubs("PMTSolid", 0., .5* PMTDiameter, .5 * PMTHeight, 0., 360. *deg);
	 PMTLV = new G4LogicalVolume(PMTSol, matPlastic, "PMTLV");
	 PMTPV = new G4PVPlacement(0, G4ThreeVector(PMTPos), PMTLV, "PMTPV", WorldLV, false, 0);

/*	 
	 // Are you optical photon?
	if ( namePostPV == "SciPV" && parName == "opticalphoton" )
	{
		if ( creProc -> GetProcessName() == "Scintillation" ) m_EA -> AddScint();
		if ( creProc -> GetProcessName() == "Cerenkov"		) m_EA -> AddCeren();

		// Once the optical photon is arrested, its step is killed.
		step -> GetTrack() -> SetTrackStatus(fStopAndKill);
*/

//========================================================
// ==== OPtical Surface =================================
	G4OpticalSurface* OpSurface = new G4OpticalSurface("OpSurf");

	G4LogicalBorderSurface* LBS = new G4LogicalBorderSurface("OpLBS",SciPV, WorldPV, OpSurface);

	OpSurface -> SetType(dielectric_dielectric);
	OpSurface -> SetModel(unified);
	OpSurface -> SetFinish(groundbackpainted);

	G4double Surf_rindex[2] = { 1.35, 1.4 };
	G4double Surf_reflectivity[2] = { 0.3, 0.3 };
	G4double Surf_efficiency[2] = { 0.8, 1.0 };

	G4MaterialPropertiesTable *SMPT = new G4MaterialPropertiesTable();

	SMPT -> AddProperty("RINDEX", energy, Surf_rindex, 2);
	SMPT -> AddProperty("REFLECTIVITY", energy, Surf_reflectivity, 2);
	SMPT -> AddProperty("EFFICIENCY", energy, Surf_efficiency , 2);


	OpSurface -> SetMaterialPropertiesTable(SMPT);

	return WorldPV;
}


void DetectorConstruction::ConstructSDandField()
{

	// MultiFunctionalDetector
	auto mfd = new G4MultiFunctionalDetector("Detector");
	G4SDManager::GetSDMpointer()->AddNewDetector(mfd);

	// Primitive Detector
	auto psPop = new G4PSPopulation("Pop");
	// Filter
	auto filterPhoton = new G4SDParticleFilter("optphoton", "opticalphoton");
	psPop -> SetFilter(filterPhoton); 

	SetSensitiveDetector("Scintillator", mfd); 

}
