#include "MapEpisode.h"
#include "../Utils/Data/Logger.h"
#include "../AppMacros.h"
#include "MapPortal.h"
#include "../Utils/StringUtility.h"
#include "MapProp.h"

MapEpisode::MapEpisode(Node& parentNode, const Vec2& localPosition, string csbPath, int _episodeNum, int lastUnlockedPortalNum, EventDispatcher* _eventDispatcher)
	: GameObject(parentNode, localPosition, csbPath)
{
   
    eventDispatcher = _eventDispatcher;
    episodeNum = _episodeNum;
    simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	dataProvider = DataProvider::getInstance();
    
    addHouse();
    addProps();
    
    addPortals(lastUnlockedPortalNum);
    
}

MapEpisode::~MapEpisode() {
    
    for (vector<MapPortal*>::iterator iterator = portalsVector.begin(); iterator != portalsVector.end(); ++iterator) {
        delete (*iterator);
    }
    portalsVector.clear();
    
    for (auto iterator = propsVector.begin(); iterator != propsVector.end(); ++iterator) {
        delete *iterator;
    }
    propsVector.clear();

   if (house != nullptr) delete house;

}


void MapEpisode::addPortals(int lastUnlockedPortalNum) {

    auto portal0 = new MapPortal(  *(  getNode().getChildByName("portal_episode_0")->getChildByName("Node")  )  , Vec2::ZERO, "MapScene/csd/portals/portal_video.csb", "hitArea", eventDispatcher, "video", "locked", episodeNum, 0);
    portalsVector.push_back(portal0);

    if (lastUnlockedPortalNum >= 0 ) portal0->setStatus("unlocked");
    
    
    int numPortals = getNumPortals(episodeNum);

    int index = 0;
    for (index = 1; index <= numPortals; ++index) {
    
        auto portalMap = new MapPortal(  *(  getNode().getChildByName("portal_episode_"+ StringUtility::toString( index ))->getChildByName("Node")  )  , Vec2::ZERO, "MapScene/csd/portals/portal_episode.csb", "hitArea", eventDispatcher, "normal", "locked", episodeNum, index);
        
       // CCLOG("in addPortals:    lastUnlockedPortalNum = %d    index = %d", lastUnlockedPortalNum, index);
        
        
       if (index <= lastUnlockedPortalNum) portalMap->setStatus("unlocked");
        
        portalsVector.push_back(portalMap);
    }

    int nightRunnerPortalNum = numPortals + 1;
    auto portalNightRunner = new MapPortal(  *(  getNode().getChildByName("portal_episode_"+ StringUtility::toString( nightRunnerPortalNum ))->getChildByName("Node")  )  , Vec2::ZERO, "MapScene/csd/portals/portal_episode.csb", "hitArea", eventDispatcher, "nightrunner", "locked", episodeNum, nightRunnerPortalNum);
    portalsVector.push_back(portalNightRunner);
    
    if ( dataProvider->isNightRunnerUnlockedForEpisode(episodeNum) ) {
        portalNightRunner->setStatus("unlocked");
    }
    
    
}


MapPortal* MapEpisode::getPortal(int numPortal) {
    return portalsVector.at(numPortal);
}
int MapEpisode::getPortalsVectorSize() {
    return (int)portalsVector.size();
}

int MapEpisode::getNumPortals(int episodeNum) {
    if (episodeNum == 1) return 5;
    if (episodeNum == 2) return 5;
    if (episodeNum == 3) return 5;
    else return 4;
}

void MapEpisode::addHouse() {
    if (episodeNum < 4) {
        house = new GameObject(  *(  getNode().getChildByName("house")->getChildByName("Node")  )  , Vec2::ZERO, "MapScene/csd/houses/house_ep"+ StringUtility::toString( episodeNum ) +".csb");
        
        house->play("house_smoke_loop", nullptr, true);
    } else {
        
        house = nullptr;
        /*
        if (episodeNum == 8) {
            house = new GameObject(  *(  getNode().getChildByName("house")->getChildByName("Node")  )  , Vec2::ZERO, "MapScene/csd/houses/house_ep3.csb");
            house->play("house_smoke_loop", nullptr, true);
        } else {
           house = nullptr;
        }
        */
        
    }
}

void MapEpisode::addProps() {
    
    if (episodeNum == 1) {
        addProp("minigranpa", "mini_granpa");
        addProp("chicken_1", "chicken");
        addProp("chicken_2", "chicken");
        addProp("chicken_3", "chicken");
        addProp("chicken_4", "chicken");
        addProp("chicken_5", "chicken");
    } else if (episodeNum == 2) {
        addProp("miniseller", "mini_seller");
        addProp("pickup", "pickup");
        addProp("chicken_1", "chicken");
        addProp("chicken_2", "chicken");
        addProp("chicken_3", "chicken");
        addProp("chicken_4", "chicken");
    } else if (episodeNum == 3) {
        addProp("scooter", "scooter");
        addProp("minipaul", "mini_paul");
        addProp("windpower_1", "windpower");
        addProp("windpower_2", "windpower");
        addProp("chicken_1", "chicken");
        addProp("chicken_2", "chicken");
        addProp("chicken_3", "chicken");
    } else if (episodeNum == 4) {
        addProp("minipaul", "mini_paul");
        addProp("minikid_1", "mini_kid_1");
        addProp("minikid_2", "mini_kid_2");
        addProp("bell", "bell");
        addProp("ball", "ball");
        addProp("chicken_1", "chicken");
        addProp("chicken_2", "chicken");
        addProp("chicken_3", "chicken");
    } else if (episodeNum == 5) {
        
        addProp("bus", "bus");
        addProp("mininight_1", "mini_night_1");
        addProp("mininight_2", "mini_night_1");
        addProp("chicken_1", "chicken");
        addProp("chicken_2", "chicken");
        addProp("chicken_3", "chicken");
        
    } else if (episodeNum == 6) {
        
        addProp("mini_gnu", "mini_gnu");
        addProp("mini_pavone", "mini_pavone");
        addProp("mini_monkey", "mini_monkey");
        addProp("chicken_1", "chicken");
        addProp("chicken_2", "chicken");
        addProp("chicken_3", "chicken");
        
    } else if (episodeNum == 7) {
        
        addProp("mini_tree_1", "mini_tree_1");
        addProp("mini_tree_2", "mini_tree_2");
        addProp("mini_tree_3", "mini_tree_3");
     
    } else if (episodeNum == 8) {
        
        addProp("mini_frog", "mini_frog");
        
    } else if (episodeNum == 9) {
        
        auto ground = new MapProp(*getNode().getChildByName("ground")->getChildByName("Node") , Vec2::ZERO, "MapScene/csd/props/ground.csb", "hit", "ground", eventDispatcher);
        propsVector.push_back(ground);
        
        
        auto ogarit = new MapProp(*ground->getChild("master_gorund/Ogarit/Node") , Vec2::ZERO, "MapScene/csd/props/mini_ogarit.csb", "hit", "mini_ogarit", eventDispatcher);
        
        propsVector.push_back(ogarit);
        
    }
}

void MapEpisode::addProp(string name, string csbName, bool flip) {
    auto prop = new MapProp(*getNode().getChildByName(name)->getChildByName("Node") , Vec2::ZERO, "MapScene/csd/props/"+csbName+".csb", "hit", name, eventDispatcher);
 
    if (flip) prop->getNode().setScaleX(-1);
    
    propsVector.push_back(prop);
}
