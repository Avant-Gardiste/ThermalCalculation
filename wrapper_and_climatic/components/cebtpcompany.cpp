#include "cebtpcompany.h"

using namespace VD6::Common;

CEBTPCompany::CEBTPCompany()
{
    _nomdeUtilisateur = "Isabelle Maréchal";
    _entreprise = "CEBTP";
    _adresse1 = "Domaine de Saint Paul";
    _adresse2 = "102, Route de Limours";
    _codePostal = "78470";
    _ville = "Saint Rémy Lès Chevreuse";
    _pays = "France";
    _tel = "01-30-85-21-56";
    _fax = "01-30-85-24-72";
    _email = "i.delevalle@cebtp.fr";
    _numdeLicence = "VD4001-02";
    _affichageMessage = "507PLOURD0102120913120913123456789000000000000SM";
    _affichageMessage2 = "OK";
}

string CEBTPCompany::nomdeUtilisateur() const
{
    return _nomdeUtilisateur;
}

void CEBTPCompany::setNomdeUtilisateur(const string &nomdeUtilisateur)
{
    _nomdeUtilisateur = nomdeUtilisateur;
}

string CEBTPCompany::entreprise() const
{
    return _entreprise;
}

void CEBTPCompany::setEntreprise(const string &entreprise)
{
    _entreprise = entreprise;
}

string CEBTPCompany::adresse1() const
{
    return _adresse1;
}

void CEBTPCompany::setAdresse1(const string &adresse1)
{
    _adresse1 = adresse1;
}

string CEBTPCompany::adresse2() const
{
    return _adresse2;
}

void CEBTPCompany::setAdresse2(const string &adresse2)
{
    _adresse2 = adresse2;
}

string CEBTPCompany::codePostal() const
{
    return _codePostal;
}

void CEBTPCompany::setCodePostal(const string &codePostal)
{
    _codePostal = codePostal;
}

string CEBTPCompany::ville() const
{
    return _ville;
}

void CEBTPCompany::setVille(const string &ville)
{
    _ville = ville;
}

string CEBTPCompany::pays() const
{
    return _pays;
}

void CEBTPCompany::setPays(const string &pays)
{
    _pays = pays;
}

string CEBTPCompany::tel() const
{
    return _tel;
}

void CEBTPCompany::setTel(const string &tel)
{
    _tel = tel;
}

string CEBTPCompany::fax() const
{
    return _fax;
}

void CEBTPCompany::setFax(const string &fax)
{
    _fax = fax;
}

string CEBTPCompany::email() const
{
    return _email;
}

void CEBTPCompany::setEmail(const string &email)
{
    _email = email;
}

string CEBTPCompany::numdeLicence() const
{
    return _numdeLicence;
}

void CEBTPCompany::setNumdeLicence(const string &numdeLicence)
{
    _numdeLicence = numdeLicence;
}

string CEBTPCompany::affichageMessage() const
{
    return _affichageMessage;
}

void CEBTPCompany::setAffichageMessage(const string &affichageMessage)
{
    _affichageMessage = affichageMessage;
}

string CEBTPCompany::affichageMessage2() const
{
    return _affichageMessage2;
}

void CEBTPCompany::setAffichageMessage2(const string &affichageMessage2)
{
    _affichageMessage2 = affichageMessage2;
}
