#include "clientinfo.h"

using namespace VD6::Common;

ClientInfo::ClientInfo()
{
    _nomdeUtilisateur = "Inconnu1";
    _entreprise = "Inconnu1";
    _adresse1 = "Adresse1 Entreprise1";
    _adresse2 = "Adresse2 Entreprise1";
    _codePostal = "000001";
    _ville = "Commune1";
    _pays = "France1";
    _tel = "00-00-00-00-001";
    _fax = "00-00-00-00-001";
    _email =  "adresse1@email.fr";
    _numdeLicence = "PLOURD";
    _affichageMessage = "1";
    _impressionDetails = "1";
    _impressionSynthese = "0";
    _impressionResultats = "0";
}

string ClientInfo::getImpressionResultats() const
{
    return _impressionResultats;
}

void ClientInfo::setImpressionResultats(const string &impressionResultats)
{
    _impressionResultats = impressionResultats;
}

string ClientInfo::getImpressionSynthese() const
{
    return _impressionSynthese;
}

void ClientInfo::setImpressionSynthese(const string &impressionSynthese)
{
    _impressionSynthese = impressionSynthese;
}

string ClientInfo::getImpressionDetails() const
{
    return _impressionDetails;
}

void ClientInfo::setImpressionDetails(const string &impressionDetails)
{
    _impressionDetails = impressionDetails;
}

string ClientInfo::getAffichageMessage() const
{
    return _affichageMessage;
}

void ClientInfo::setAffichageMessage(const string &affichageMessage)
{
    _affichageMessage = affichageMessage;
}

string ClientInfo::getNumdeLicence() const
{
    return _numdeLicence;
}

void ClientInfo::setNumdeLicence(const string &numdeLicence)
{
    _numdeLicence = numdeLicence;
}

string ClientInfo::getEmail() const
{
    return _email;
}

void ClientInfo::setEmail(const string &email)
{
    _email = email;
}

string ClientInfo::getFax() const
{
    return _fax;
}

void ClientInfo::setFax(const string &fax)
{
    _fax = fax;
}

string ClientInfo::getTel() const
{
    return _tel;
}

void ClientInfo::setTel(const string &tel)
{
    _tel = tel;
}

string ClientInfo::getPays() const
{
    return _pays;
}

void ClientInfo::setPays(const string &pays)
{
    _pays = pays;
}

string ClientInfo::getVille() const
{
    return _ville;
}

void ClientInfo::setVille(const string &ville)
{
    _ville = ville;
}

string ClientInfo::getCodePostal() const
{
    return _codePostal;
}

void ClientInfo::setCodePostal(const string &codePostal)
{
    _codePostal = codePostal;
}

string ClientInfo::getAdresse2() const
{
    return _adresse2;
}

void ClientInfo::setAdresse2(const string &adresse2)
{
    _adresse2 = adresse2;
}

string ClientInfo::getAdresse1() const
{
    return _adresse1;
}

void ClientInfo::setAdresse1(const string &adresse1)
{
    _adresse1 = adresse1;
}

string ClientInfo::getEntreprise() const
{
    return _entreprise;
}

void ClientInfo::setEntreprise(const string &entreprise)
{
    _entreprise = entreprise;
}

string ClientInfo::getNomdeUtilisateur() const
{
    return _nomdeUtilisateur;
}

void ClientInfo::setNomdeUtilisateur(const string &nomdeUtilisateur)
{
    _nomdeUtilisateur = nomdeUtilisateur;
}
