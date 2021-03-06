#include "unistd.h"
#include "lua.h"
#include "lauxlib.h"
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <android/log.h>
#include <dirent.h>
#include <linux/input.h>
#include <malloc.h>
#include "ldroidlib.h"
#include "ldoinput.h"
#include "lshellcmd.h"


/*
 * 调用系统的sleep
 * para：传入毫秒，调用系统的微秒
 * return： 返回值的个数
 */
static int system_sleep(lua_State *L) {
    long secs = lua_tointeger(L, -1);
    usleep(secs * 1000);
    LOGD("input sleep %d", secs);
    return 0;
}

static int system_init(lua_State *L) {
    if (init_uinput_dev() < 0) {
    } else{
        LOGD("init uinput dev success");
    }

    return 0;
}

/*
 * 模拟点击事件
 */
static int system_click(lua_State *L) {


    usleep(100000);

    int x = lua_tointeger(L, -2); /*获取参数X*/
    int y = lua_tointeger(L, -1); /*获取参数Y*/
    LOGD("input touch Event: x=%d,y=%d", x, y);

    int result = write_click_event(x, y);
    if(result < 0)
        LOGE("error emulate click event");

    return 0;
}

/*
 * 获取屏幕的大小
 * @return：返回屏幕的w和h 两个返回值
 */
static int system_getScreenSize(lua_State *L) {

    struct fb_var_screeninfo fb_var;
    int fd = open(DEV_GRAPHICS, O_RDONLY);

    if (fd < 0) {
        LOGE("open %s failed", DEV_GRAPHICS);
        lua_pushnumber(L, -1);
        lua_pushnumber(L, -1);
        return 2;
    }

    fd = ioctl(fd, FBIOGET_VSCREENINFO, &fb_var);

    if (fd < 0) {
        lua_pushnumber(L, -1);
        lua_pushnumber(L, -1);
        return 2;
    }

    lua_pushnumber(L, fb_var.xres);
    lua_pushnumber(L, fb_var.yres);

    close(fd);
    return 2;
}

/*
 * 模拟发送back 按键
 */
static int system_back(lua_State *L) {

    usleep(100000);

    int result = write_back_event();
    if(result < 0)
        LOGE("error emulate back event");
    return 0;
}

/*
 * 模拟按键音up
 */
static int system_volumeUp(lua_State *L){
    usleep(100000);

    int result = write_volume_up();
    if(result < 0)
        LOGE("error emulate volume_up event");
    return 0;
}

/*
 *模拟按键音down
 */
static int system_volumeDown(lua_State *L){
    usleep(100000);

    int result = write_volume_down();
    if(result < 0)
        LOGE("error emulate volume_down event");
    return 0;
}

static int system_inputText(lua_State *L){
    const char *text = lua_tostring(L, -1); /*获取参数X*/
    int result = input_text(text);
    if(result < 0)
        LOGE("error emulate inputText event");
    return 0;
}

static int system_home(lua_State *L){
    usleep(100000);


    int result = write_home_event();
    if(result < 0)
        LOGE("error emulate home event");
    return 0;
}

static int system_homePage(lua_State *L){
    usleep(100000);

    int result = write_home_page_event();
    if(result < 0)
        LOGE("error emulate home page event");
    return 0;
}

static int system_menu(lua_State *L){
    usleep(100000);

    int result = write_menu_event();
    if(result < 0)
        LOGE("error emulate menu event");
    return 0;
}

static int system_runApp(lua_State *L){

    const char *action = lua_tostring(L, -1); /*获取参数X*/

    int result = run_app(action);
    if(result < 0)
        LOGE("error run app:%s", action);
    return 0;
}

static int system_killApp(lua_State *L){

    const char *packageName = lua_tostring(L, -1); /*获取参数X*/

    int result = kill_app(packageName);
    if(result < 0)
        LOGE("error kill app:%s", packageName);
    return 0;
}

static int system_touchDown(lua_State *L){

    int x = lua_tointeger(L, -2); /*获取参数X*/
    int y = lua_tointeger(L, -1); /*获取参数Y*/

    int result = touchDown(x, y);
    if(result < 0)
        LOGE("error system_touchDown ret is %d", result);
    return 0;
}

static int system_touchScroll(lua_State *L){

    int x = lua_tointeger(L, -2); /*获取参数X*/
    int y = lua_tointeger(L, -1); /*获取参数Y*/

    int result = touchScroll(x, y);
    if(result < 0)
        LOGE("system_touchScroll");
    return 0;
}

static int system_touchUp(lua_State *L){
    int x = lua_tointeger(L, -2); /*获取参数X*/
    int y = lua_tointeger(L, -1); /*获取参数Y*/

    int result = touchUp(x, y);
    if(result < 0)
        LOGE("system_touchUp ret is %d", result);
    return 0;
}

static int system_close(lua_State *L){
    int result = destroy();
    if(result < 0)
        LOGE("destroy dev");
    return 0;
}

static int system_test(lua_State *L){
    LOGD("just a test");
    return 0;
}

static const struct luaL_Reg droidlib[] = {
        {"getScreenSize", system_getScreenSize},
        {"runApp",        system_runApp},
        {"killApp",       system_killApp},

        {"init",          system_init},
        {"sleep",         system_sleep},
        {"click",         system_click},
        {"back",          system_back}, //测试未通过
        {"volumeUp",      system_volumeUp},
        {"volumeDown",    system_volumeDown},
        {"inputText",     system_inputText},
        {"home",          system_home},
        {"homePage",      system_homePage},
        {"menu",          system_menu},
        {"touchUp",       system_touchUp},
        {"touchScroll",   system_touchScroll},
        {"touchDown",     system_touchDown},
        {"close",         system_close},
        {"test",          system_test},
        {NULL, NULL}  /*the end*/
};

int luaopen_droidlib(lua_State *L) {
    luaL_newlib(L, droidlib);
    LOGD("open droid lib");
    return 1;
}