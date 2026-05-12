#include <iostream>
using namespace std;
#include "user.h"
// ructors
user::user(string u_n, string u_e, string u_p, string u_phn) : user_name(u_n), user_email(u_e), user_password(u_p), user_phonenumber(u_phn)
{
}
user::~user()
{
}
// setter and getter for name
void user::setname_user( string u_n)
{
    user_name = u_n;

}
string user::getname_user() 
{
    return user_name;
}
// setter and getter for email

void user::setemail_user( string u_e)
{
    user_email = u_e;
}
string user::getemail_user() 
{
    return user_email;
}
// setter and getter for password
void user::setpassword_user( string u_p)
{
    user_password = u_p;
}
string user::getpassword_user() 
{
    return user_password;
}
// setter and getter for phone number
void user::setphonenumber_user( string u_phn)
{
    user_phonenumber = u_phn;
}
string user::getphonenumber_user() 
{
    return user_phonenumber;
}
// setter abd getter for id
void user::setid_user(long long u_i)
{   
user_id = u_i;
}
long long user::getid_user()
{
    return user_id;
}
