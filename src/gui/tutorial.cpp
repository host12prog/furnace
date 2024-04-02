/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2024 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "gui.h"
#include "../ta-log.h"
#include "IconsFontAwesome4.h"
#include "imgui_internal.h"

#include "gif_load.h"

#define TS FurnaceGUITutorialStep

#ifdef _WIN32
#include <windows.h>
#include "../utfutils.h"
#else
#include <dirent.h>
#endif

enum FurnaceCVObjectTypes {
  CV_NULL=0,
  CV_PLAYER,
  CV_BULLET,
  CV_ENEMY_BULLET,
  CV_BOMB,
  CV_ENEMY_BOMB,
  CV_EXPLOSION,
  CV_ENEMY,
  CV_FURBALL,
  CV_MINE,
  CV_POWERUP_P,
  CV_POWERUP_S,
  CV_EXTRA_LIFE
};

struct FurnaceCVObject {
  FurnaceCV* cv;
  unsigned short type;
  unsigned short spriteDef[512];
  unsigned char spriteWidth, spriteHeight;
  bool dead;
  short x, y;
  unsigned char z, prio;
  short collX0, collX1, collY0, collY1;
  
  virtual void collision(FurnaceCVObject* other);
  virtual void tick();
  FurnaceCVObject(FurnaceCV* p):
    cv(p),
    type(0),
    spriteWidth(2),
    spriteHeight(2),
    dead(false),
    x(0),
    y(0),
    z(0),
    prio(1),
    collX0(0),
    collX1(15),
    collY0(0),
    collY1(15) {
    memset(spriteDef,0,512*sizeof(unsigned short));
    spriteDef[0]=4;
    spriteDef[1]=5;
    spriteDef[2]=36;
    spriteDef[3]=37;
  }
  virtual ~FurnaceCVObject() {
  }
};

void FurnaceCVObject::collision(FurnaceCVObject* other) {
}

void FurnaceCVObject::tick() {
}

struct FurnaceCVPlayer: FurnaceCVObject {
  short subX, subY;
  short speedX, speedY;
  unsigned char shootDir;
  unsigned char animFrame;
  unsigned char invincible;
  unsigned char shotTimer;

  void collision(FurnaceCVObject* other);
  void tick();
  FurnaceCVPlayer(FurnaceCV* p):
    FurnaceCVObject(p),
    subX(0),
    subY(0),
    speedX(0),
    speedY(0),
    shootDir(2),
    animFrame(0),
    invincible(120),
    shotTimer(4) {
      type=CV_PLAYER;
      spriteWidth=3;
      spriteHeight=3;
      spriteDef[0]=0x10;
      spriteDef[1]=0x11;
      spriteDef[2]=0x12;
      spriteDef[3]=0x30;
      spriteDef[4]=0x31;
      spriteDef[5]=0x32;
      spriteDef[6]=0x50;
      spriteDef[7]=0x51;
      spriteDef[8]=0x52;
      collX0=0;
      collX1=23;
      collY0=0;
      collY1=23;
    }
};

struct FurnaceCVBullet: FurnaceCVObject {
  short subX, subY;
  short speedX, speedY;
  unsigned char bulletType, orient, life;
  
  void killBullet();
  void setType(unsigned char t);
  void collision(FurnaceCVObject* other);
  void tick();
  FurnaceCVBullet(FurnaceCV* p):
    FurnaceCVObject(p),
    subX(0),
    subY(0),
    speedX(0),
    speedY(0),
    bulletType(0),
    orient(0),
    life(0) {
    type=CV_BULLET;
    spriteWidth=1;
    spriteHeight=1;
    spriteDef[0]=6;
    collX0=2;
    collX1=5;
    collY0=2;
    collY1=5;
  }
};

struct FurnaceCVEnemyBullet: FurnaceCVObject {
  short subX, subY;
  short speedX, speedY;
  unsigned char animFrame, bulletType;
  
  void setType(unsigned char type);
  void tick();
  FurnaceCVEnemyBullet(FurnaceCV* p):
    FurnaceCVObject(p),
    subX(0),
    subY(0),
    speedX(0),
    speedY(0),
    animFrame(rand()&0xff),
    bulletType(0) {
    type=CV_ENEMY_BULLET;
    spriteWidth=1;
    spriteHeight=1;
    spriteDef[0]=6;
    collX0=2;
    collX1=5;
    collY0=2;
    collY1=5;
  }
};

struct FurnaceCVEnemy1: FurnaceCVObject {
  unsigned char enemyType;
  unsigned char health;
  unsigned char orient;
  unsigned char stopped;
  unsigned char animFrame;
  short nextTime, shootTime;
  unsigned char shootCooldown;

  void collision(FurnaceCVObject* other);

  void tick();
  void setType(unsigned char type);
  FurnaceCVEnemy1(FurnaceCV* p):
    FurnaceCVObject(p),
    enemyType(0),
    health(1),
    orient(rand()&3),
    stopped(0),
    animFrame(0),
    nextTime(64+(rand()%600)),
    shootTime(8),
    shootCooldown(0) {
    type=CV_ENEMY;
    spriteDef[0]=0x200;
    spriteDef[1]=0x201;
    spriteDef[2]=0x220;
    spriteDef[3]=0x221;
  }
};

struct FurnaceCVEnemyVortex: FurnaceCVObject {
  unsigned char stopped;
  unsigned char animFrame;
  short nextTime, shootTime, speedX, speedY;

  void collision(FurnaceCVObject* other);

  void tick();
  FurnaceCVEnemyVortex(FurnaceCV* p):
    FurnaceCVObject(p),
    stopped(0),
    animFrame(0),
    nextTime(4+(rand()%140)),
    shootTime(360),
    speedX((rand()%5)-2),
    speedY((rand()%5)-2) {
    type=CV_ENEMY;
    spriteDef[0]=0x480;
    spriteDef[1]=0x481;
    spriteDef[2]=0x4a0;
    spriteDef[3]=0x4a1;
  }
};

struct FurnaceCVExplTiny: FurnaceCVObject {
  unsigned char animFrame;

  void tick();
  FurnaceCVExplTiny(FurnaceCV* p):
    FurnaceCVObject(p),
    animFrame(0) {
    type=CV_EXPLOSION;
    spriteWidth=1;
    spriteHeight=1;
    spriteDef[0]=8;
  }
};

struct FurnaceCVExplMedium: FurnaceCVObject {
  unsigned char animFrame;

  void tick();
  FurnaceCVExplMedium(FurnaceCV* p):
    FurnaceCVObject(p),
    animFrame(0) {
    type=CV_EXPLOSION;
    spriteWidth=3;
    spriteHeight=3;
    spriteDef[0]=0x210;
    spriteDef[1]=0x211;
    spriteDef[2]=0x212;
    spriteDef[3]=0x230;
    spriteDef[4]=0x231;
    spriteDef[5]=0x232;
    spriteDef[6]=0x250;
    spriteDef[7]=0x251;
    spriteDef[8]=0x252;
  }
};

struct FurnaceCVFurBallMedium: FurnaceCVObject {
  unsigned char animFrame;

  void tick();
  FurnaceCVFurBallMedium(FurnaceCV* p):
    FurnaceCVObject(p),
    animFrame(0) {
    type=CV_FURBALL;
    spriteWidth=3;
    spriteHeight=3;
    spriteDef[0]=0x410;
    spriteDef[1]=0x411;
    spriteDef[2]=0x412;
    spriteDef[3]=0x430;
    spriteDef[4]=0x431;
    spriteDef[5]=0x432;
    spriteDef[6]=0x450;
    spriteDef[7]=0x451;
    spriteDef[8]=0x452;
  }
};

struct FurnaceCVFurBallLarge: FurnaceCVObject {
  unsigned char animFrame;

  void tick();
  FurnaceCVFurBallLarge(FurnaceCV* p):
    FurnaceCVObject(p),
    animFrame(0) {
    type=CV_FURBALL;
    spriteWidth=4;
    spriteHeight=4;
    spriteDef[0]=0x390;
    spriteDef[1]=0x391;
    spriteDef[2]=0x392;
    spriteDef[3]=0x393;
    spriteDef[4]=0x3b0;
    spriteDef[5]=0x3b1;
    spriteDef[6]=0x3b2;
    spriteDef[7]=0x3b3;
    spriteDef[8]=0x3d0;
    spriteDef[9]=0x3d1;
    spriteDef[10]=0x3d2;
    spriteDef[11]=0x3d3;
    spriteDef[12]=0x3f0;
    spriteDef[13]=0x3f1;
    spriteDef[14]=0x3f2;
    spriteDef[15]=0x3f3;
  }
};

struct FurnaceCVMine: FurnaceCVObject {
  void collision(FurnaceCVObject* other);
  FurnaceCVMine(FurnaceCV* p):
    FurnaceCVObject(p) {
      type=CV_MINE;
    }
};

struct FurnaceCVPowerupP: FurnaceCVObject {
  unsigned char life;
  void collision(FurnaceCVObject* other);
  void tick();
  FurnaceCVPowerupP(FurnaceCV* p):
    FurnaceCVObject(p),
    life(255) {
      type=CV_POWERUP_P;
    }
};

struct FurnaceCVPowerupS: FurnaceCVObject {
  unsigned char life;
  void collision(FurnaceCVObject* other);
  void tick();
  FurnaceCVPowerupS(FurnaceCV* p):
    FurnaceCVObject(p),
    life(255) {
      type=CV_POWERUP_S;
    }
};

struct FurnaceCVExtraLife: FurnaceCVObject {
  unsigned char life;
  void collision(FurnaceCVObject* other);
  void tick();
  FurnaceCVExtraLife(FurnaceCV* p):
    FurnaceCVObject(p),
    life(255) {
      type=CV_EXTRA_LIFE;
    }
};

struct FurnaceCV {
  SDL_Surface* surface;
  unsigned char* prioBuf;
  DivEngine* e;
  unsigned char* tileData;
  
  // state
  unsigned short* curStage;
  int stageWidth, stageHeight;

  const char* typeAddr;
  unsigned char typeDelay;
  int typeX, typeY;
  int typeXStart, typeYStart;
  int typeXEnd, typeYEnd;

  int textWait, curText, transWait;
  int ticksToInit;

  bool inGame, inTransition, newHiScore, playSongs, pleaseInitSongs;
  unsigned char lives, respawnTime, stage, shotType;
  int score;
  int hiScore;
  short lastPlayerX, lastPlayerY;
  short fxChanBase, fxInsBase;
  
  // graphics
  unsigned short tile0[56][80];
  unsigned short tile1[56][80];
  unsigned short scrollX[2];
  unsigned short scrollY[2];
  unsigned char bgColor;
  std::vector<FurnaceCVObject*> sprite;
  // this offset is applied to sprites.
  int viewX, viewY;

  // input
  unsigned char joyInputPrev;
  unsigned char joyPressed;
  unsigned char joyReleased;
  unsigned char joyInput;

  template<typename T> T* createObject(short x=0, short y=0);
  void buildStage(int which);

  void putText(int fontBase, bool fontHeight, String text, int x, int y);

  void startTyping(const char* text, int x, int y);

  void soundEffect(int ins, int chan, int note);
  void stopSoundEffect(int ins, int chan, int note);

  void addScore(int amount);

  void typeTick();

  void rasterH(int scanline);
  void render(unsigned char joyIn);
  void tileDataRead(struct GIF_WHDR* data);
  void loadInstruments();
  bool init(DivEngine* eng);
  void unload();

  FurnaceCV():
    surface(NULL),
    e(NULL),
    tileData(NULL),
    curStage(NULL),
    stageWidth(0),
    stageHeight(0),
    typeAddr(NULL),
    typeDelay(0),
    typeX(0),
    typeY(0),
    typeXStart(0),
    typeYStart(0),
    typeXEnd(39),
    typeYEnd(27),
    textWait(60),
    curText(0),
    transWait(0),
    ticksToInit(2),
    inGame(false),
    inTransition(false),
    newHiScore(false),
    playSongs(true),
    pleaseInitSongs(false),
    lives(3),
    respawnTime(0),
    stage(0),
    shotType(0),
    score(0),
    hiScore(25000),
    lastPlayerX(0),
    lastPlayerY(0),
    fxChanBase(-1),
    fxInsBase(-1),
    bgColor(0),
    viewX(0),
    viewY(0),
    joyInputPrev(0),
    joyPressed(0),
    joyReleased(0),
    joyInput(0) {
    memset(tile0,0,80*56*sizeof(short));
    memset(tile1,0,80*56*sizeof(short));

    scrollX[0]=0;
    scrollX[1]=0;
    scrollY[0]=0;
    scrollY[1]=0;
  }
};

static const char* cvText[]={
  // intro
  "Play demo songs?\n"
  "- Down: Play current song\n"
  "- Up: Play demo songs",

  "Welcome to Combat Vehicle!\n\n"
  "Controls:\n"
  "X - Shoot      Arrow Key - Move\n"
  "Z - Special    Esc - Quit",

  "GAME OVER",

  "Conglaturation!\n"
  "\n"
  "With high score beat, it\n"
  "enables Serious Mode.\n"
  "The User is now peace.",

  "Restart Furnace to apply\n"
  "changes.",

  "Restart Furnace to apply\n"
  "changes.",

  "Restart Furnace to apply\n"
  "changes.",

  "Restart Furnace to apply\n"
  "changes.",

  "Restart Furnace to apply\n"
  "changes.",

  "Never gonna give STOP posting\n"
  "about Rick Astley",

  "I'M TIRED OF SEEING IT",

  "My friends on TikTok rickroll\n"
  "me",

  "On Discord's fucking rickroll",

  "I was in a server. Right?",

  "And AAAAALLL of the channels\n"
  "are just Never Gonna Give You Up.",

  "I've searched for Half-Life 3\n"
  "and the video I watched it and\n"
  "I said: Hey Babe, Never Gonna\n"
  "Give You Up HAHA",

  "Diiiiiiiing Diiiiiiiiiiiing\n"
  "Diiing Diiiiiiing Diiiiiiiiiing\n"
  "Didididiiiiiiiing",

  "I fucking looked at the DefleMask\n"
  "1.2 teaser trailer and I said\n"
  "That's a rickroll",

  "I've looked at my [REDACTED],\n"
  "I think of the scientist and I go\n"
  "[REDACTED], more like never gonna\n"
  "[REDACTED] up\n",

  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",

  // this is totally intentional. do not attempt to fix it.
  (const char*)1
};

void FurnaceGUI::initTutorial() {
  tutorials[GUI_TUTORIAL_OVERVIEW]=FurnaceGUITutorialDef("Overview",{
    TS(
      "hello! this is the Furnace tutorial!\n"
      "I will teach you how to use Furnace.\n"
      "if you wish to skip these tutorials, click on one of the Skip buttons. otherwise, click the " ICON_FA_CHEVRON_RIGHT " icon to continue."
    ),
    TS(
      "Furnace is a chiptune tracker!\n"
      "in a tracker, the song is written down in patterns, which are lists of notes, instruments and effects to play.\n"
      "a playhead scrolls down through these patterns, and plays the notes that are written in them as it moves.\n"
      "think of it as a piano roll, but replace the dots in the position of notes with note names (e.g. A-4)."
    ),
    TS(
      "these are called \"patterns\" because they may appear more than once in the song.\n"
      "this is useful for (in example) percussion, avoiding duplication.\n"
      "the order in which these patterns appear is determined by an order list which also scrolls down as the playhead moves between patterns."
    ),
    TS(
      "this is the Pattern window. it displays a pattern (which contains the notes and stuff).",
      -1,
      [this]() {
        highlightWindow("Pattern");
      },
      [this]() {
        nextWindow=GUI_WINDOW_PATTERN;
      }
    ),
    TS(
      "this is the Orders window. it displays which patterns are going to play.",
      -1,
      [this]() {
        highlightWindow("Orders");
      },
      [this]() {
        nextWindow=GUI_WINDOW_ORDERS;
      }
    ),
    TS(
      "this is the Instruments window. it shows a list of instruments (sounds) in the song.",
      -1,
      [this]() {
        highlightWindow("Instruments");
      },
      [this]() {
        nextWindow=GUI_WINDOW_INS_LIST;
      }
    ),
    TS(
      "this is the Song Information window, which allows you to change some song properties.",
      -1,
      [this]() {
        highlightWindow("Song Info##Song Information");
      },
      [this]() {
        nextWindow=GUI_WINDOW_SONG_INFO;
      }
    ),
    TS(
      "this is the Speed window, which contains speed parameters.",
      -1,
      [this]() {
        highlightWindow("Speed");
      },
      [this]() {
        nextWindow=GUI_WINDOW_SPEED;
      }
    ),
    TS(
      "and here are the Play Controls. you can use these to play the song and do some other things.\n"
      "now that I am done explaining the interface, let's make a song!",
      -1,
      [this]() {
        highlightWindow("Play Controls");
      },
      [this]() {
        nextWindow=GUI_WINDOW_EDIT_CONTROLS;
      }
    ),
    TS(
      "we'll start by creating an instrument.\n"
      "while it's possible to work without instruments, we would be stuck with the default sound!\n"
      "so let's create one... for that you click on the " ICON_FA_PLUS " button in the Instruments window."
    ),
    TS(
      ""
    ),
    TS(
      "now let's type in some notes!\n"
      "first, enable Edit Mode with the Space key.\n"
      "after that, click on the pattern editor to focus it (the first empty column to be specific).\n"
    ),
    TS(
      "the keyboard layout for inserting notes resembles that of a piano:\n"
      "- Z-M: low octave\n"
      "- Q-U: mid octave\n"
      "- I-P and beyond: high octave\n"
      "the keys one row above the mentioned octaves are the upper keys of a piano.\n"
      "let's press some of these keys to insert notes!"
    ),
    TS(
      ""
    ),
    TS(
      "and now, let's play the song! hit Enter to play it (and press it while playing to stop)."
    ),
    TS(
      ""
    ),
    TS(
      "great!\n"
      "by the way, you can move around the pattern view using the arrow keys or by clicking in the pattern."
    ),
    TS(
      "now let me teach you about these columns in the pattern editor.\n"
      "each big column represents a channel.\n"
      "a channel consists of five (or more) smaller columns:\n"
      "- the first column contains notes.\n"
      "- the second one represents the instruments to play (these will be filled in automatically when you have an instrument selected).\n"
      "- the third one has volume changes (will explain these later).\n"
      "- the last two ones are effects and effect values (you can have multiple effect columns, but that's something I will be covering later as well.)\n"
      "the instrument, volume and effect columns are continuous. this means that if nothing is specified, the last value will be used."
    ),
    TS(
      "let's add some volume changes to show you what I mean."
    ),
    TS(
      ""
    ),
    TS(
      "as you can hear, volume changes affects all notes which are placed next to, or after it.\n"
      "let's place some bass notes."
    ),
    TS(
      ""
    ),
    TS(
      "oh wait! the keyboard layout only contains 2 octaves!\n"
      "however, we can change the octave range by using the Octave setting in the play/edit controls."
    ),
    TS(
      ""
    ),
    TS(
      "now let's type in the notes..."
    ),
    TS(
      ""
    ),
    TS(
      "...and play this?"
    ),
    TS(
      ""
    ),
    TS(
      "cool, huh? but we're running out of space here.\n"
      "let's expand the song."
    ),
    TS(
      "for that we go in the Orders window, which contains the order these patterns will appear in.\n"
      "the first column is position while the other columns contain pattern numbers of every channel."
    ),
    TS(
      "clicking on the " ICON_FA_PLUS " button adds one row to the orders..."
    ),
    TS(
      ""
    ),
    TS(
      "and then clicking on a cell of the first column takes us there."
    ),
    TS(
      ""
    ),
    TS(
      "now let's add more to the song."
    ),
    TS(
      ""
    ),
    TS(
      "and after that, let's hear it!\n"
      "note that playing the song by pressing Enter will play from the current position in the Orders view - that is, order 1!\n"
      "we want to play from order 0 (the first order), so we go back to it first and then hit Enter."
    ),
    TS(
      ""
    ),
    TS(
      "congratulations! you made it\n"
      "what else?"
    )
  });
}

void FurnaceGUI::syncTutorial() {
//  tutorial.userComesFrom=e->getConfInt("tutUserComesFrom",0);
  tutorial.introPlayed=e->getConfBool("tutIntroPlayed",false);
  tutorial.protoWelcome=e->getConfBool("tutProtoWelcome2",false);
}

void FurnaceGUI::commitTutorial() {
//  e->setConf("tutUserComesFrom",tutorial.userComesFrom);
  e->setConf("tutIntroPlayed",tutorial.introPlayed);
  e->setConf("tutProtoWelcome2",tutorial.protoWelcome);
}

void FurnaceGUI::activateTutorial(FurnaceGUITutorials which) {
  /*
  if (tutorial.protoWelcome && !tutorial.taken[which] && !ImGui::IsPopupOpen((const char*)NULL,ImGuiPopupFlags_AnyPopupId|ImGuiPopupFlags_AnyPopupLevel) && curTutorial==-1 && introPos>=10.0) {
    logV("activating tutorial %d.",which);
    curTutorial=which;
    curTutorialStep=0;
  }
  */
}

void FurnaceGUI::initRandomDemoSong() {
  std::vector<String> subDirs;
#if !defined(IS_MOBILE) && defined(FURNACE_DATADIR) && defined(SHOW_OPEN_ASSETS_MENU_ENTRY)
  String demoPath=FURNACE_DATADIR;
  demoPath+=DIR_SEPARATOR_STR;
  demoPath+="demos";
#else
#ifdef IS_MOBILE
  String demoPath="/storage/emulated/0/demos";
#else
  String demoPath="demos";
#endif
#endif

  logW("searching for demos in %s...",demoPath);

#ifdef _WIN32
  WIN32_FIND_DATAW de;
  String realDemoPath=demoPath;
  realDemoPath+=DIR_SEPARATOR_STR;
  realDemoPath+="*";
  HANDLE d=FindFirstFileW(utf8To16(realDemoPath.c_str()).c_str(),&de);
  if (d==INVALID_HANDLE_VALUE) {
    realDemoPath="..";
    realDemoPath+=DIR_SEPARATOR_STR;
    realDemoPath+="demos";
    realDemoPath+=DIR_SEPARATOR_STR;
    realDemoPath+="*";
    logW("OH NO");
    HANDLE d=FindFirstFileW(utf8To16(realDemoPath.c_str()).c_str(),&de);
    if (d==INVALID_HANDLE_VALUE) {
      logW("dang it");
      return;
    }
  }
  do {
    String u8Name=utf16To8(de.cFileName);
    if (u8Name==".") continue;
    if (u8Name=="..") continue;
    if (de.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) {
      String newPath=demoPath;
      newPath+=DIR_SEPARATOR_STR;
      newPath+=u8Name;
      logW("adding subdir %s",newPath);
      subDirs.push_back(newPath);
    } else if (strstr(u8Name.c_str(),".fur")!=NULL) {
      String newPath=demoPath;
      newPath+=DIR_SEPARATOR_STR;
      newPath+=u8Name;
      randomDemoSong.push_back(newPath);
    }
  } while (FindNextFileW(d,&de)!=0);
  FindClose(d);
#else
  DIR* d=opendir(demoPath.c_str());
  if (d==NULL) {
    demoPath="..";
    demoPath+=DIR_SEPARATOR_STR;
    demoPath+="demos";
    logW("OH NO");
    d=opendir(demoPath.c_str());
    if (d==NULL) {
      logW("dang it");
      return;
    }
  }

  struct dirent* de=NULL;
  while (true) {
    de=readdir(d);
    if (de==NULL) break;
    if (strcmp(de->d_name,".")==0) continue;
    if (strcmp(de->d_name,"..")==0) continue;
    if (de->d_type==DT_DIR) {
      String newPath=demoPath;
      newPath+=DIR_SEPARATOR_STR;
      newPath+=de->d_name;
      logW("adding subdir %s",newPath);
      subDirs.push_back(newPath);
    } else if (de->d_type==DT_REG && strstr(de->d_name,".fur")!=NULL) {
      String newPath=demoPath;
      newPath+=DIR_SEPARATOR_STR;
      newPath+=de->d_name;
      randomDemoSong.push_back(newPath);
    }
  }
  closedir(d);
#endif

  for (String& i: subDirs) {
#ifdef _WIN32
    WIN32_FIND_DATAW de1;
    String realI=i;
    realI+=DIR_SEPARATOR_STR;
    realI+="*.fur";
    HANDLE d1=FindFirstFileW(utf8To16(realI.c_str()).c_str(),&de1);
    if (d1==INVALID_HANDLE_VALUE) continue;
    do {
      String u8Name=utf16To8(de1.cFileName);
      String newPath=i;
      newPath+=DIR_SEPARATOR_STR;
      newPath+=u8Name;
      randomDemoSong.push_back(newPath);
    } while (FindNextFileW(d1,&de1)!=0);
    FindClose(d1);
#else
    DIR* d1=opendir(i.c_str());
    if (d1==NULL) continue;

    struct dirent* de1=NULL;
    while (true) {
      de1=readdir(d1);
      if (de1==NULL) break;
      if (strcmp(de1->d_name,".")==0) continue;
      if (strcmp(de1->d_name,"..")==0) continue;
      if (de1->d_type==DT_REG && strstr(de1->d_name,".fur")!=NULL) {
        String newPath=i;
        newPath+=DIR_SEPARATOR_STR;
        newPath+=de1->d_name;
        randomDemoSong.push_back(newPath);
      }
    }
    closedir(d1);
#endif
  }
}

bool FurnaceGUI::loadRandomDemoSong() {
  if (randomDemoSong.empty()) return false;
  String which=randomDemoSong[rand()%randomDemoSong.size()];
  logW("RDS LOAD... %s",which);
  load(which);
  return true;
}

void FurnaceGUI::drawTutorial() {
  // welcome
  if (!tutorial.protoWelcome) {
    ImGui::OpenPopup("Welcome");
  }
  if (ImGui::BeginPopupModal("Welcome",NULL,ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoTitleBar)) {
    ImGui::PushFont(bigFont);
    ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x-ImGui::CalcTextSize("Welcome!").x)*0.5);
    ImGui::Text("Welcome!");
    ImGui::PopFont();

    ImGui::Text("welcome to Furnace, the biggest open-source chiptune tracker!");

    ImGui::Separator();

    ImGui::TextWrapped("here are some tips to get you started:");
    
    ImGui::TextWrapped(
      "- add an instrument by clicking on + in Instruments\n"
      "- click on the pattern view to focus it\n"
      "- channel columns have the following, in this order: note, instrument, volume and effects\n"
      "- hit space bar while on the pattern to toggle Edit Mode\n"
      "- click on the pattern or use arrow keys to move the cursor\n"
      "- values (instrument, volume, effects and effect values) are in hexadecimal\n"
      "- hit enter to play/stop the song\n"
      "- extend the song by adding more orders in the Orders window\n"
      "- click on the Orders matrix to change the patterns of a channel (left click increases; right click decreases)"
    );

    ImGui::TextWrapped(
      "if you need help, you may:\n"
      "- read the manual (a file called manual.pdf)\n"
      "- ask for help in Discussions (https://github.com/tildearrow/furnace/discussions), the Furnace Discord (https://discord.gg/EfrwT2wq7z) or Furnace in Revolt (official: https://rvlt.gg/GRPS6tmc)"
    );

    ImGui::Separator();

    ImGui::TextWrapped("if you find any issues, be sure to report them! the issue tracker is here: https://github.com/tildearrow/furnace/issues");

    if (ImGui::Button("OK")) {
      tutorial.protoWelcome=true;
      commitTutorial();
      ImGui::CloseCurrentPopup();
    }

    ImGui::SetWindowPos(ImVec2(
      (canvasW-ImGui::GetWindowSize().x)*0.5,
      (canvasH-ImGui::GetWindowSize().y)*0.5
    ));
    ImGui::EndPopup();
  }

  // tutorial
  if (curTutorial>=0 && curTutorial<GUI_TUTORIAL_MAX) {
    FurnaceGUITutorialStep& step=tutorials[curTutorial].steps[curTutorialStep];
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(canvasW,canvasH));
    if (ImGui::Begin("Tutorial",NULL,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoBackground|ImGuiWindowFlags_NoDocking)) {
      ImDrawList* dl=ImGui::GetWindowDrawList();
      if (step.run!=NULL) {
        step.run();
      } else {
        ImU32 col=ImGui::GetColorU32(uiColors[GUI_COLOR_MODAL_BACKDROP]);
        dl->AddRectFilled(
          ImVec2(0,0),
          ImVec2(canvasW,canvasH),
          col
        );
      }
      if (step.text[0]) {
        ImVec2 avail=ImGui::GetContentRegionAvail();
        ImVec2 textSize=ImGui::CalcTextSize(step.text,NULL,false,avail.x);
        textSize.x+=ImGui::GetStyle().WindowPadding.y*2.0f;
        textSize.y+=ImGui::GetStyle().WindowPadding.y*2.0f+ImGui::GetFrameHeightWithSpacing();
        if (textSize.x>avail.x) textSize.x=avail.x;
        if (textSize.y>avail.y) textSize.y=avail.y;

        ImGui::SetCursorPos(ImVec2(
          (canvasW-textSize.x)*0.5,
          (canvasH-textSize.y)*0.5
        ));

        dl->AddRectFilled(
          ImGui::GetCursorPos(),
          ImVec2(
            ImGui::GetCursorPos().x+textSize.x,
            ImGui::GetCursorPos().y+textSize.y
          ),
          ImGui::GetColorU32(ImGuiCol_PopupBg)
        );

        if (ImGui::BeginChild("TutText",textSize,true,ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse)) {
          ImGui::TextWrapped("%s",step.text);

          if (ImGui::Button("Skip")) {
            tutorial.taken[curTutorial]=true;
            curTutorial=-1;
            curTutorialStep=0;
          }
          ImGui::SameLine();
          if (ImGui::Button(ICON_FA_CHEVRON_RIGHT)) {
            curTutorialStep++;
            if (step.runAfter!=NULL) step.runAfter();
            if (curTutorialStep>=(int)tutorials[curTutorial].steps.size()) {
              tutorial.taken[curTutorial]=true;
              curTutorial=-1;
              curTutorialStep=0;
            } else {
              if (tutorials[curTutorial].steps[curTutorialStep].runBefore) tutorials[curTutorial].steps[curTutorialStep].runBefore();
            }
          }
        }
        ImGui::EndChild();
      }
    }
    ImGui::End();
  }

  if (cvOpen) {
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(canvasW,canvasH));
    if (ImGui::Begin("Combat Vehicle",&cvOpen,ImGuiWindowFlags_NoDocking|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_Modal|ImGuiWindowFlags_NoTitleBar)) {
      ImVec2 dpadLoc=ImVec2(canvasW*0.25,canvasH*0.85); 
      ImVec2 buttonLoc=ImVec2(canvasW*0.75,canvasH*0.85);
      float oneUnit=canvasW*0.15;

      ImVec2 dpadUpStart=ImVec2(
        dpadLoc.x-oneUnit*1.5,
        dpadLoc.y-oneUnit*1.5
      );
      ImVec2 dpadUpEnd=ImVec2(
        dpadLoc.x+oneUnit*1.5,
        dpadLoc.y-oneUnit*0.5
      );
      ImVec2 dpadLeftEnd=ImVec2(
        dpadLoc.x-oneUnit*0.5,
        dpadLoc.y+oneUnit*1.5
      );
      ImVec2 dpadDownStart=ImVec2(
        dpadLoc.x-oneUnit*1.5,
        dpadLoc.y+oneUnit*0.5
      );
      ImVec2 dpadDownEnd=ImVec2(
        dpadLoc.x+oneUnit*1.5,
        dpadLoc.y+oneUnit*1.5
      );
      ImVec2 dpadRightStart=ImVec2(
        dpadLoc.x+oneUnit*0.5,
        dpadLoc.y-oneUnit*1.5
      );

      ImVec2 buttonBStart=ImVec2(
        buttonLoc.x-oneUnit*1.25,
        buttonLoc.y-oneUnit*0.5
      );
      ImVec2 buttonBEnd=ImVec2(
        buttonLoc.x-oneUnit*0.25,
        buttonLoc.y+oneUnit*0.5
      );
      ImVec2 buttonAStart=ImVec2(
        buttonLoc.x+oneUnit*0.25,
        buttonLoc.y-oneUnit*0.5
      );
      ImVec2 buttonAEnd=ImVec2(
        buttonLoc.x+oneUnit*1.25,
        buttonLoc.y+oneUnit*0.5
      );

      unsigned char touchControls=0;

      if (mobileUI) {
        for (TouchPoint& i: activePoints) {
          // B
          if (i.x>=buttonBStart.x && i.y>=buttonBStart.y &&
              i.x<=buttonBEnd.x && i.y<=buttonBEnd.y) {
            touchControls|=1;
          }
          // A
          if (i.x>=buttonAStart.x && i.y>=buttonAStart.y &&
              i.x<=buttonAEnd.x && i.y<=buttonAEnd.y) {
            touchControls|=2;
          }
          // up
          if (i.x>=dpadUpStart.x && i.y>=dpadUpStart.y &&
              i.x<=dpadUpEnd.x && i.y<=dpadUpEnd.y) {
            touchControls|=16;
          }
          // down
          if (i.x>=dpadDownStart.x && i.y>=dpadDownStart.y &&
              i.x<=dpadDownEnd.x && i.y<=dpadDownEnd.y) {
            touchControls|=32;
          }
          // left
          if (i.x>=dpadUpStart.x && i.y>=dpadUpStart.y &&
              i.x<=dpadLeftEnd.x && i.y<=dpadLeftEnd.y) {
            touchControls|=64;
          }
          // right
          if (i.x>=dpadRightStart.x && i.y>=dpadRightStart.y &&
              i.x<=dpadDownEnd.x && i.y<=dpadDownEnd.y) {
            touchControls|=128;
          }
        }
      }

      if (cv==NULL) {
        initRandomDemoSong();
        cv=new FurnaceCV;
        cv->init(e);
        cv->hiScore=cvHiScore;
        e->setNumTimesPlayed(-1);
        shaderEditor=false;
      }
      if (cvTex==NULL) {
        cvTex=rend->createTexture(true,320,224,false);
      }

      if (cv->pleaseInitSongs) {
        cv->pleaseInitSongs=false;
        if (cv->playSongs) {
          if (loadRandomDemoSong()) {
            cv->loadInstruments();
          }
        }
      }

      WAKE_UP;

      if (cv->inTransition && cv->transWait==1) {
        // load random demo song
        if (cv->playSongs) {
          if (loadRandomDemoSong()) {
            cv->loadInstruments();
            e->changeSongP(0);
            e->setOrder(0);
            e->play();
          }
        }
      }

      cv->render(touchControls);
      
      if (cv->hiScore>cvHiScore) {
        cvHiScore=cv->hiScore;
      }

      if (cvTex!=NULL) {
        SDL_LockSurface(cv->surface);
        rend->updateTexture(cvTex,cv->surface->pixels,320*4);
        SDL_UnlockSurface(cv->surface);

        ImDrawList* dl=ImGui::GetForegroundDrawList();

        ImVec2 p0, p1;

        if (((double)canvasH/(double)canvasW)>0.7) {
          if (mobileUI) {
            p0=ImVec2(0.0,0.0);
            p1=ImVec2(canvasW,canvasW*0.7);
          } else {
            p0=ImVec2(0.0,(canvasH-(canvasW*0.7))*0.5);
            p1=ImVec2(canvasW,canvasW*0.7+(canvasH-(canvasW*0.7))*0.5);
          }
        } else {
          p0=ImVec2((canvasW-(canvasH/0.7))*0.5,0.0);
          p1=ImVec2((canvasH/0.7)+(canvasW-(canvasH/0.7))*0.5,canvasH);
        }

        dl->AddRectFilled(ImVec2(0,0),ImVec2(canvasW,canvasH),0xff000000);

        dl->AddImage(rend->getTextureID(cvTex),p0,p1);

        if (mobileUI) {
          dl->AddRect(dpadUpStart,dpadUpEnd,0xff0000ff,0,0,dpiScale);
          dl->AddRect(dpadUpStart,dpadLeftEnd,0xff00ffff,0,0,dpiScale);
          dl->AddRect(dpadDownStart,dpadDownEnd,0xff00ff00,0,0,dpiScale);
          dl->AddRect(dpadRightStart,dpadDownEnd,0xffff0000,0,0,dpiScale);

          dl->AddRect(buttonBStart,buttonBEnd,0xffffff00,0,0,dpiScale);
          dl->AddRect(buttonAStart,buttonAEnd,0xffff00ff,0,0,dpiScale);
        }
      }
    }
    ImGui::End();

    if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
      time_t timet=time(NULL);
      struct tm* curtm=localtime(&timet);
      if (curtm!=NULL) {
        if (curtm->tm_mon==3 && curtm->tm_mday==1) {
          if (cvHiScore>25000) {
            if (cv!=NULL) {
              cv->unload();
              delete cv;
              cv=NULL;
            }
            cvOpen=false;
          }
        } else {
          if (cv!=NULL) {
            cv->unload();
            delete cv;
            cv=NULL;
          }
          cvOpen=false;
        }
      } else {
        if (cv!=NULL) {
          cv->unload();
          delete cv;
          cv=NULL;
        }
        cvOpen=false;
      }
    }
  }
}

// helper functions

void FurnaceGUI::highlightWindow(const char* winName) {
  ImDrawList* dl=ImGui::GetWindowDrawList();
  ImU32 col=ImGui::GetColorU32(uiColors[GUI_COLOR_MODAL_BACKDROP]);

  ImGuiWindow* win=ImGui::FindWindowByName(winName);
  if (win!=NULL) {
    ImVec2 start=win->Pos;
    ImVec2 end=ImVec2(
      start.x+win->Size.x,
      start.y+win->Size.y
    );

    dl->AddRectFilled(
      ImVec2(0,0),
      ImVec2(start.x,canvasH),
      col
    );
    dl->AddRectFilled(
      ImVec2(start.x,0),
      ImVec2(canvasW,start.y),
      col
    );
    dl->AddRectFilled(
      ImVec2(end.x,start.y),
      ImVec2(canvasW,canvasH),
      col
    );
    dl->AddRectFilled(
      ImVec2(start.x,end.y),
      ImVec2(end.x,canvasH),
      col
    );

    dl->AddRect(start,end,ImGui::GetColorU32(uiColors[GUI_COLOR_TEXT]),0,0,3.0f*dpiScale);
  } else {
    dl->AddRectFilled(
      ImVec2(0,0),
      ImVec2(canvasW,canvasH),
      col
    );
  }
}

FurnaceGUITutorialDef::FurnaceGUITutorialDef(const char* n, std::initializer_list<FurnaceGUITutorialStep> step):
  name(n) {
  steps=step;
}

