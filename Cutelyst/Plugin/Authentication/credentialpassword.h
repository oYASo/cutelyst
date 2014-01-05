#ifndef CUTELYSTPLUGIN_CREDENTIALPASSWORD_H
#define CUTELYSTPLUGIN_CREDENTIALPASSWORD_H

#include <Cutelyst/Plugin/authentication.h>

namespace Cutelyst {
namespace Plugin {

class CredentialPassword : public Authentication::Credential
{
public:
    CredentialPassword();

    Authentication::User authenticate(Context *ctx, Authentication::Realm *realm, const CStringHash &authinfo);

    QString passwordField() const;
    void setPasswordField(const QString &fieldName);

private:
    bool checkPassword(const Authentication::User &user, const CStringHash &authinfo);

    QString m_passwordField;
};

} // namespace CutelystPlugin
}

#endif // CUTELYSTPLUGIN_CREDENTIALPASSWORD_H