#include "nodeinfos.h"

NodeInfos::NodeInfos(QObject *parent) : QObject(parent)
{
}

bool NodeInfos::init(QString Idi, QString IPi, QString Locatei, int Typei, QString Belongi, QString Principali, QString Installeri, QString Maintaineri, QString DataConfigi, QString SelfInfoi, QString LastUploadi, QString SelfDatei, QString Remarki, QString InstallDatei, float Loi, float Lii, float GasConcentrationi, float Temperaturei, float PHI, float Densityi, float Conductivityi, float OxygenConcentrationi, float MetalConcentrationi, float SolidsConcentrationi, float FloatingSolidsConcentrationi, float TotalPhosphorusi, float TotalNitrogeni, float TotalOrganicCarboni, float BiologicalOxygenDemandi, float ChemicalOxygenDemandi, int BacteriaCounti, int StaphylococcusCounti)
{
    Id = Idi;
    IP = IPi;
    Locate = Locatei;
    Type = Typei;
    Belong = Belongi;
    Principal = Principali;
    Installer = Installeri;
    Maintainer = Maintaineri;
    DataConfig = DataConfigi;
    SelfInfo = SelfInfoi;
    LastUpload = LastUploadi;
    SelfDate = SelfDatei;
    Remark = Remarki;
    InstallDate = InstallDatei;
    Lo = Loi;
    Li = Lii;
    GasConcentration = GasConcentrationi;
    Temperature = Temperaturei;
    PH = PHI;
    Density = Densityi;
    Conductivity = Conductivityi;
    OxygenConcentration = OxygenConcentrationi;
    MetalConcentration = MetalConcentrationi;
    SolidsConcentration = SolidsConcentrationi;
    FloatingSolidsConcentration = FloatingSolidsConcentrationi;
    TotalPhosphorus = TotalPhosphorusi;
    TotalNitrogen = TotalNitrogeni;
    TotalOrganicCarbon = TotalOrganicCarboni;
    BiologicalOxygenDemand = BiologicalOxygenDemandi;
    ChemicalOxygenDemand = ChemicalOxygenDemandi;
    BacteriaCount = BacteriaCounti;
    return true;
}