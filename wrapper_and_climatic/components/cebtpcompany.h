#ifndef CEBTPCOMPANY_H
#define CEBTPCOMPANY_H

#include "components_global.h"

#include <string>
#include <vector>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT CEBTPCompany
{
public:
    /**
     * @brief
     *
     */
    CEBTPCompany();

    /**
     * @brief
     *
     * @return string
     */
    string nomdeUtilisateur() const;
    /**
     * @brief
     *
     * @param nomdeUtilisateur
     */
    void setNomdeUtilisateur(const string &nomdeUtilisateur);

    /**
     * @brief
     *
     * @return string
     */
    string entreprise() const;
    /**
     * @brief
     *
     * @param entreprise
     */
    void setEntreprise(const string &entreprise);

    /**
     * @brief
     *
     * @return string
     */
    string adresse1() const;
    /**
     * @brief
     *
     * @param adresse1
     */
    void setAdresse1(const string &adresse1);

    /**
     * @brief
     *
     * @return string
     */
    string adresse2() const;
    /**
     * @brief
     *
     * @param adresse2
     */
    void setAdresse2(const string &adresse2);

    /**
     * @brief
     *
     * @return string
     */
    string codePostal() const;
    /**
     * @brief
     *
     * @param codePostal
     */
    void setCodePostal(const string &codePostal);

    /**
     * @brief
     *
     * @return string
     */
    string ville() const;
    /**
     * @brief
     *
     * @param ville
     */
    void setVille(const string &ville);

    /**
     * @brief
     *
     * @return string
     */
    string pays() const;
    /**
     * @brief
     *
     * @param pays
     */
    void setPays(const string &pays);

    /**
     * @brief
     *
     * @return string
     */
    string tel() const;
    /**
     * @brief
     *
     * @param tel
     */
    void setTel(const string &tel);

    /**
     * @brief
     *
     * @return string
     */
    string fax() const;
    /**
     * @brief
     *
     * @param fax
     */
    void setFax(const string &fax);

    /**
     * @brief
     *
     * @return string
     */
    string email() const;
    /**
     * @brief
     *
     * @param email
     */
    void setEmail(const string &email);

    /**
     * @brief
     *
     * @return string
     */
    string numdeLicence() const;
    /**
     * @brief
     *
     * @param numdeLicence
     */
    void setNumdeLicence(const string &numdeLicence);

    /**
     * @brief
     *
     * @return string
     */
    string affichageMessage() const;
    /**
     * @brief
     *
     * @param affichageMessage
     */
    void setAffichageMessage(const string &affichageMessage);

    /**
     * @brief
     *
     * @return string
     */
    string affichageMessage2() const;
    /**
     * @brief
     *
     * @param affichageMessage2
     */
    void setAffichageMessage2(const string &affichageMessage2);

private:
    string _nomdeUtilisateur; /**< TODO: describe */
    string _entreprise; /**< TODO: describe */
    string _adresse1; /**< TODO: describe */
    string _adresse2; /**< TODO: describe */
    string _codePostal; /**< TODO: describe */
    string _ville; /**< TODO: describe */
    string _pays; /**< TODO: describe */
    string _tel; /**< TODO: describe */
    string _fax; /**< TODO: describe */
    string _email; /**< TODO: describe */
    string _numdeLicence; /**< TODO: describe */
    string _affichageMessage; /**< TODO: describe */
    string _affichageMessage2; /**< TODO: describe */

};

}
}
#endif // CEBTPCOMPANY_H
