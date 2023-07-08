#include <QtGlobal>
#include <QString>

const qreal GRIVATY=1.75;
const qreal JUMP_SPEED=-19;
const qreal XSPEED=3.5;

const qreal playerX=100;
const qreal playerY=387;
const qreal playerW=12;
const qreal playerH=40;
const qreal OBJXSPEED=10.5;
const qreal OBJYSPEED=12.5;

const qreal floorX=0;
const qreal floorY=428;
const qreal floorW=758;
const qreal floorH=500;

const qreal floorLeftX=442;
const qreal floorLeftY=428;
const qreal floorLeftW=758;
const qreal floorLeftH=500;

const int backgroundR=171;
const int backgroundG=210;
const int backgroundB=214;
//basical
const QString PLAYERLEFT=":/images/playerLeft.png";
const QString PLAYERRIGHT=":/images/playerRight.png";
const QString PLAYERLEFTMOVE=":/images/playerLeftMove.png";
const QString PLAYERRIGHTMOVE=":/images/playerRightMove.png";
const QString GROUND=":/images/ground.png";
const QString WATER=":/images/water.png";
const QString LEFTLIFT=":/images/leftlift.png";
const QString RIGHTLIFT=":/images/rightlift.png";
const QString LEFTJUMPLIFT=":/images/jumpliftL.png";
const QString RIGHTJUMPLIFT=":/images/jumpliftR.png";
const QString BLOOD[18] = {":/images/blood1.png",
                           ":/images/blood2.png",
                           ":/images/blood3.png",
                           ":/images/blood4.png",
                           ":/images/blood5.png",
                           ":/images/blood6.png",
                           ":/images/blood7.png",
                           ":/images/blood8.png",
                           ":/images/blood9.png",
                           ":/images/blood10.png",
                           ":/images/blood11.png",
                           ":/images/blood12.png",
                           ":/images/blood13.png",
                           ":/images/blood14.png",
                           ":/images/blood15.png",
                           ":/images/blood16.png",
                           ":/images/blood17.png",
                           ":/images/blood18.png"};


//level 1
const qreal boardX = 250;
const qreal boardY = 393;
const qreal boardW = 35;
const qreal boardH = 35;
const qreal boardSpace = 30;
const QString BOARD=":/images/board.png";
const QString BANNER1 = ":/images/banner1.png";
//level 2
const QString BLACKBULL1=":/images/blackbull1.png";
const QString BLACKBULL2=":/images/blackbull2.png";
const QString REDBULL1=":/images/redbull1.png";
const QString REDBULL2=":/images/redbull2.png";
const QString YELLOWBULL1=":/images/yellowbull1.png";
const QString YELLOWBULL2=":/images/yellowbull2.png";
const qreal bullX=-100;
const qreal bullY=371;
const qreal bullW=75;
const qreal bullH=58;
//level 3
const qreal keyX = 400;
const qreal keyY = 393;
const qreal keyW = 34;
const qreal keyH = 24;
const qreal wallX = 550;
const qreal wallY = 171;
const qreal wallW = 32;
const qreal wallH = 256;
const QString KEY=":/images/key.png";
const QString WALL=":/images/wall.png";
const QString BANNER3 = ":/images/banner3.png";
//level 4
const qreal man1X = 550;
const qreal man1Y = 388;
const qreal man1W = 24;
const qreal man1H = 40;
const qreal man2X = 549;
const qreal man2Y = 385;
const qreal man2W = 25;
const qreal man2H = 43;
const qreal bridgeY = 427;
const QString MAN1=":/images/man1.png";
const QString MAN2=":/images/man2.png";
const QString BRIDGE=":/images/bridge.png";
const QString LEFTBRIDGE=":/images/leftbridge.png";
const QString BANNER4 = ":/images/banner4.png";
const QString SCENE4= ":/images/scene4.png";//6 also needs
//level 5
const qreal activeBoardX = 550;
const qreal activeBoardY = 393;
const qreal activeBoardW = 30;
const qreal activeBoardH = 35;
const qreal activeBoardSpace = 80;
const qreal active1Start = 2;
const qreal gun0Start = active1Start + 2;
const qreal gun1Start = gun0Start + 4;
const qreal gun2Start = gun1Start + 1;
const qreal run0Start = gun2Start + 2;
const qreal bulletX = 530;
const qreal bulletY = 393;
const qreal bulletW = 20;
const qreal bulletH = 16;
const QString DEAD=":/images/dead.png";
const QString POLICELEFT=":/images/policeleft.png";
const QString POLICERIGHT=":/images/policeright.png";
const QString POLICELEFTMOVE=":/images/policemoveleft.png";
const QString POLICERIGHTMOVE=":/images/policemoveright.png";
const QString SHOCK=":images/shock.png";
const QString BULLETLEFT=":/images/bulletleft.png";
const QString BULLETRIGHT=":/images/bulletright.png";
const QString SHOOTLEFT=":/images/shootleft.png";
const QString SHOOTRIGHT=":/images/shootright.png";
const QString GREENGRASS1=":/images/greengrass1.png";
const QString GREENGRASS2=":/images/greengrass2.png";
const QString ACTIVEBOARD0=":/images/activeboard0.png";
const QString ACTIVEBOARD1=":/images/activeboard1.png";
const QString ACTIVEBOARD2=":/images/activeboard2.png";
const QString ACTIVEBOARD3=":/images/activeboard3.png";
const QString ACTIVEBOARD4=":/images/activeboard4.png";
const QString ACTIVEBOARD5=":/images/activeboard5.png";
const QString ACTIVEBOARD6=":/images/activeboard6.png";
const QString ACTIVEBOARD7=":/images/activeboard7.png";
//level 6
const qreal DOGW=40;
const qreal DOGH=24;
const qreal TRAPW=40;
const qreal TRAPH=35;
const QString BANNER61=":/images/bannerl6.png";
const QString BANNER62=":/images/bannerl7.png";
const QString DOG1=":/images/dog1.png";
const QString DOG2=":/images/dog2.png";
const QString DOG3=":/images/dog3.png";
const QString DOGMAN1=":/images/dogman1.png";
const QString DOGMAN2=":/images/dogman2.png";
const QString WOMAN1=":/images/woman1.png";
const QString WOMAN2=":/images/woman2.png";
const QString WOMANHIT1=":/images/womanhit1.png";
const QString WOMANHIT2=":/images/womanhit2.png";
const QString RIGHTGROUND=":/images/rightground.png";
//level 7
const QString SHELF=":/images/shelf.png";
const QString GRASS=":/images/grass.png";//4 also needs
const QString RGRASS=":/images/rgrass.png";
const QString GHOSTLEFT=":images/ghostleft.png";
const QString GHOSTRIGHT=":images/ghostright.png";
const QString BGHOSTLEFT=":images/bghostleft.png";
const QString BGHOSTRIGHT=":/images/bghostright.png";
const qreal ghostW=28;
const qreal ghostH=40;
//level 8
const qreal shelfX = 150;
const qreal shelfY = 384;
const qreal shelfW = 43;
const qreal shelfH = 44;
const qreal arrowX = 150;
const qreal arrowY = 423;
const qreal arrowW = 40;
const qreal arrowH = 5;
const qreal dragonX = 620;
const qreal dragonW = 137;
const qreal dragonH = 133;
const qreal dragonY = floorY - dragonH;
const qreal bombW = 22;
const qreal bombH = 24;
const qreal bombX = dragonX - bombW;
const qreal bombY = dragonY + 15; //TODO
const qreal amplitude = 220;
const qreal omega = 0.03;
const QString WEAPON=":/images/weapon.png";
const QString WEAPONSHELF=":/images/weaponshelf.png";
const QString DRAGON1=":/images/dragon1.png";
const QString DRAGON2=":/images/dragon2.png";
const QString DRAGON3=":/images/dragon3.png";
const QString BOMB=":/images/bomb.png";
const QString BLACKHEART=":/images/blackheart.png";
const QString WHITEHEART=":/images/whiteheart.png";
const QString REDHEART=":/images/redheart.png";
