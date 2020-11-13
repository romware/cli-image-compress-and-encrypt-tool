#define MAX_USERNAME_SIZE 15
#define MAX_PASSWORD_LENGTH 20
#define MAX_USERS 20
#define USER_DB_NAME "userdata"

/*******************************************************************************
Structure to hold the users username and password
*******************************************************************************/
struct user
{
	char name[MAX_USERNAME_SIZE];
	char password[MAX_PASSWORD_LENGTH];
};
typedef struct user user_t;

/*******************************************************************************
List of function prototypes in this file
*******************************************************************************/
int login(user_t userList[MAX_USERS], int userIndex);
int addUser(user_t userList[MAX_USERS], int userIndex);
void saveUserData(const user_t userList[MAX_USERS], int userIndex);
int readUserData(user_t userList[MAX_USERS]);
