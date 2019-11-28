#pragma once
#include "position.h"
#include "packet.h"
#include <list> 
#include "node.h"
#include "router.h"
#include "map.h"
#include "tools.h"

class drone : public node
{
	public:
		struct routerPosRow
		{
			ip publicIP;
			router* rou;
		};

		struct pacList
		{
			packet pac;
			bool canDelete;
		};

		list<pacList> packetBuff;
		list<routerPosRow> routerPosTables;
		map* m;

		drone();
		drone(int x, int y, map* p_m);
		void sendRequestToRouter(router* p_rou);
		void addToRouterPosTable(string p_pubIP, router* p_rou);
		void moveToRouter(router* p_rou, map* p_m);
		void deliverBuffer();
		router* tableLookup(ip p_ip);
};

