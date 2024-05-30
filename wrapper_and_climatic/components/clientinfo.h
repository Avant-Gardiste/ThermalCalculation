#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "components_global.h"

#include <string>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT ClientInfo
{
public:
    /**
     * @brief
     *
     */
    ClientInfo();

    /**
     * @brief
     *
     * @return string
     */
    string getNomdeUtilisateur() const;
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
    string getEntreprise() const;
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
    string getAdresse1() const;
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
    string getAdresse2() const;
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
    string getCodePostal() const;
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
    string getVille() const;
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
    string getPays() const;
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
    string getTel() const;
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
    string getFax() const;
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
    string getEmail() const;
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
    string getNumdeLicence() const;
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
    string getAffichageMessage() const;
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
    string getImpressionDetails() const;
    /**
     * @brief
     *
     * @param impressionDetails
     */
    void setImpressionDetails(const string &impressionDetails);

    /**
     * @brief
     *
     * @return string
     */
    string getImpressionSynthese() const;
    /**
     * @brief
     *
     * @param impressionSynthese
     */
    void setImpressionSynthese(const string &impressionSynthese);

    /**
     * @brief
     *
     * @return string
     */
    string getImpressionResultats() const;
    /**
     * @brief
     *
     * @param impressionResultats
     */
    void setImpressionResultats(const string &impressionResultats);

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
    string _impressionDetails; /**< TODO: describe */
    string _impressionSynthese; /**< TODO: describe */
    string _impressionResultats; /**< TODO: describe */

};

}
}
#endif // CLIENTINFO_H
