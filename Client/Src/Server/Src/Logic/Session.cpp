#include "stdafx.h"
#include "Session.h"
#include <Game/PlayerGOMServer.h>
#include <GameWorld.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::Init()
		{
			// Server side
			::Game::Player::Register(kClientChatMessage, &Session::HandleChatMessage);
			::Game::Player::Register(kClientInitialData, &Session::HandleInitialData);
			::Game::Player::Register(kClientPlayerMoveState, &Session::HandlePlayerMoveState);
			
		}
		//--------------------------------------------------------------------------------
		Session::Session(unsigned int id, ::Game::GameServer* server) : ::Game::Player(id, server) 
		{
		}
		//--------------------------------------------------------------------------------
		Session::~Session()
		{
			try
			{
				std::for_each(mEventLinks.begin(), mEventLinks.end(), [](boost::signals::connection& pConnection)
				{
					pConnection.disconnect();
				});

				TheMassiveMessageMgr->GetGOMDatabase()->Get<Game::PlayerGOMServer>()->Remove(::Game::kTransactionFull, GetKey());
			}
			catch(...)
			{
				System::Log::Debug("Session::~Session() error");
			}
		}
		//--------------------------------------------------------------------------------
		void Session::OnSynchronize()
		{
		}
		//--------------------------------------------------------------------------------
		void Session::OnEnterAwareness()
		{
			//Write(TheGameWorld->GetWorldManager().GetWorldState().ToPacket(kServerWorldState));
		}
		//--------------------------------------------------------------------------------
		std::string Session::GetName()
		{
			return mName;
		}
		//--------------------------------------------------------------------------------
	}
}