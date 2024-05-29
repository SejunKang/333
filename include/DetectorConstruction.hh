#ifndef DETECTORCONSTRUCTION_HH
 #define DETECTORCONSTRUCTION_HH

 #include "G4VUserDetectorConstruction.hh"
 #include "G4UnionSolid.hh"
 #include "G4OpticalSurface.hh"
 #include "G4LogicalBorderSurface.hh"

 #include "G4Box.hh"
 #include "G4Tubs.hh"

 class G4VPhysicalVolume;
 class G4LogicalVolume;

 class DetectorConstruction : public G4VUserDetectorConstruction
 {
 public:
     DetectorConstruction();
     virtual ~DetectorConstruction() override;

     virtual G4VPhysicalVolume *Construct() override;
     virtual void ConstructSDandField() override;

 private:
     // Dimensions and detector setup
     G4double Cylsize, CylDiameter, CylHeight, PMTDiameter, PMTHeight;

	 // Geometry objects: World
	 G4Box* WorldSol;
	 G4LogicalVolume* WorldLV;
	 G4VPhysicalVolume* WorldPV;

	 // Geometry objects: Lab
	 G4Box* LabSol;
	 G4LogicalVolume* LabLV;
	 G4VPhysicalVolume* LabPV;

	 // Geometry objects : Cylinder
	 G4Tubs* CylSol;
	 G4LogicalVolume* CylLV;
	 G4VPhysicalVolume* CylPV;

	 // Geometry objects : Cone
	 G4LogicalVolume* ConeLV;
	 G4VPhysicalVolume* ConePV;

	 // Geometry objects: Scint
	 G4UnionSolid* SciSol;
	 G4LogicalVolume* SciLV;
	 G4VPhysicalVolume* SciPV;

	 // Geometry objects: PMT
	 G4Tubs* PMTSol;
	 G4LogicalVolume* PMTLV;
	 G4VPhysicalVolume* PMTPV;

	 // Surface objects: Scint
	 G4OpticalSurface* SciOps;
	 G4LogicalBorderSurface* SciLBS;

	 // Materials
	 G4MaterialPropertiesTable* SciMPT;
	 G4MaterialPropertiesTable* AirMPT;

	 // Surface objects: Air
	 G4OpticalSurface* AirOpS;
	 G4OpticalSurface* SciOpS;
 };


#endif

