/**
 * The header file of MENU.
 *
 * @Team	MR12/MCS
 * @Author 	William Ho, Sam
 * @Date	4/9 2020
 */
#ifndef AP_MENU_H_
#define AP_MENU_H_

// The array size of menu item index.
#define IDX_SIZE	  3

// The array size of menu item description.
#define STRING_SIZE	128

/* Added by William Ho on 2020/4/14 start */
// the definition of function
/**
  * The function handled from console input.
  *
  * @param 1	the command index
  * @param 2	the function(key) name
  *
  * @return if processed successfully, then return 1; or return 0.
  */
typedef int (*handleFun)(int, char *);
/* Added by William Ho on 2020/4/14 end */

// The structure of menu item
typedef struct MenuItem mItem;
typedef struct MenuItem {
	char idx[IDX_SIZE];				// The index of item
	int functionIndex;
	char functionName[STRING_SIZE];
	char desc[STRING_SIZE];			// The description of item
	handleFun handleAction; 		// Added by William Ho on 2020/4/14 start
	int enable;						// The item is enabled or not(default is enabled)
	int parentMenu_pool_index;
	mItem **parentMenu_pool;		// The parent level Menu Item
	int parentMenuCount;			// The count of parent Menu
	int chidMenu_pool_index;
	char szChildMenuString[STRING_SIZE];
	mItem **chidMenu_pool;			// The child level Menu Item
	int childMenuCount;				// The count of child Menu
} MENU_ITEM;

/**
 * To Initiate the base menu.
 *
 * @param **menu_pool 	the root pool of menu item
 * @param poolCount 	the count of menu item
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int initMenu(mItem **menu_pool, int poolCount);

/**
 * To generate program menu.
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int createMenu();

/**
 * To retrive a string key for menu item.
 *
 * @param count the count of menu item
 * @param key   the function(key) name
 */
void getActionKey(int count, char *key);

/* Moved from MUT library by William Ho on 2020/4/14 start */
/**
 * To initiate sub menu.
 *
 * @param *fConfig			the pointer of file
 * @param *pStrSubMenuTag	the pointer of tag name of sub menu
 * @param *pSubPoolCount	the pointer of sub pool count
 *
 * @return if processed successfully, then return the array pointer of mItem; or return NULL.
 */
mItem ** initSubMenu(FILE *fConfig, char *pStrSubMenuTag, int *pSubPoolCount);

/**
 * To handle the action key of root menu from input.(deprecated)
 *
 * @param idx the command index
 * @param key the function(key) name
 *
 * @return if processing successfully, then return 1; or return 0. 
 */
int handle_root_menu_action(int idx, char *key);

/**
 * To initiate main menu.
 *
 * @param *fConfig	the pointer of file
 *
 * @return if processed successfully, then return the array pointer of mItem; or return NULL.
 */
mItem ** initMainMenu(FILE *fConfig);

/**
 * To find the index of command with function(key) name.
 *
 * @param 1 the function(key) name
 * @param 2 the pointer of command index
 *
 * @return if processing successfully, then return 1; or return 0.
 */
static int (*findCMDIdxByKey)(char *, int *);  //If you don't include 'static' and compile using Ubuntu 22.04 GCC version, you will encounter 'multiple definition' error.

/**
 * To find the pointer of function with function(key) name.
 *
 * @param 1 the function(key) name
 *
 * @return if processing successfully, then return handleFun; or return NULL.
 */
static handleFun (*findFunPtrByKey)(char *);  //If you don't include 'static' and compile using Ubuntu 22.04 GCC version, you will encounter 'multiple definition' error.

/**
 * To initiate UI Menu.
 *
 * @param *fConfig		the pointer of file
 * @param *findIdx  	the function pinter of searching a command index
 * @param *findFunPtr   the function pinter of searching a function pointer
 *
 * @return if no error, then return 1; or return 0.
 */
int INIT_UI_MENU(FILE *fConfig, int (*findIdx)(char *, int *), handleFun (*findFunPtr)(char *));
/* Moved from MUT library by William Ho on 2020/4/14 start */

#endif //AP_MENU_H_
