/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "Common.h"

#include "WorldSession.h"
#include "WorldPacket.h"

class Player;

enum ChatNotify
{
    CHAT_JOINED_NOTICE                = 0x00,           //+ "%s joined channel.";
    CHAT_LEFT_NOTICE                  = 0x01,           //+ "%s left channel.";
    //CHAT_SUSPENDED_NOTICE             = 0x01,           // "%s left channel.";
    CHAT_YOU_JOINED_NOTICE            = 0x02,           //+ "Joined Channel: [%s]"; -- You joined
    //CHAT_YOU_CHANGED_NOTICE           = 0x02,           // "Changed Channel: [%s]";
    CHAT_YOU_LEFT_NOTICE              = 0x03,           //+ "Left Channel: [%s]"; -- You left
    CHAT_WRONG_PASSWORD_NOTICE        = 0x04,           //+ "Wrong password for %s.";
    CHAT_NOT_MEMBER_NOTICE            = 0x05,           //+ "Not on channel %s.";
    CHAT_NOT_MODERATOR_NOTICE         = 0x06,           //+ "Not a moderator of %s.";
    CHAT_PASSWORD_CHANGED_NOTICE      = 0x07,           //+ "[%s] Password changed by %s.";
    CHAT_OWNER_CHANGED_NOTICE         = 0x08,           //+ "[%s] Owner changed to %s.";
    CHAT_PLAYER_NOT_FOUND_NOTICE      = 0x09,           //+ "[%s] Player %s was not found.";
    CHAT_NOT_OWNER_NOTICE             = 0x0A,           //+ "[%s] You are not the channel owner.";
    CHAT_CHANNEL_OWNER_NOTICE         = 0x0B,           //+ "[%s] Channel owner is %s.";
    CHAT_MODE_CHANGE_NOTICE           = 0x0C,           //?
    CHAT_ANNOUNCEMENTS_ON_NOTICE      = 0x0D,           //+ "[%s] Channel announcements enabled by %s.";
    CHAT_ANNOUNCEMENTS_OFF_NOTICE     = 0x0E,           //+ "[%s] Channel announcements disabled by %s.";
    CHAT_MODERATION_ON_NOTICE         = 0x0F,           //+ "[%s] Channel moderation enabled by %s.";
    CHAT_MODERATION_OFF_NOTICE        = 0x10,           //+ "[%s] Channel moderation disabled by %s.";
    CHAT_MUTED_NOTICE                 = 0x11,           //+ "[%s] You do not have permission to speak.";
    CHAT_PLAYER_KICKED_NOTICE         = 0x12,           //? "[%s] Player %s kicked by %s.";
    CHAT_BANNED_NOTICE                = 0x13,           //+ "[%s] You are banned from that channel.";
    CHAT_PLAYER_BANNED_NOTICE         = 0x14,           //? "[%s] Player %s banned by %s.";
    CHAT_PLAYER_UNBANNED_NOTICE       = 0x15,           //? "[%s] Player %s unbanned by %s.";
    CHAT_PLAYER_NOT_BANNED_NOTICE     = 0x16,           //+ "[%s] Player %s is not banned.";
    CHAT_PLAYER_ALREADY_MEMBER_NOTICE = 0x17,           //+ "[%s] Player %s is already on the channel.";
    CHAT_INVITE_NOTICE                = 0x18,           //+ "%2$s has invited you to join the channel '%1$s'.";
    CHAT_INVITE_WRONG_FACTION_NOTICE  = 0x19,           //+ "Target is in the wrong alliance for %s.";
    CHAT_WRONG_FACTION_NOTICE         = 0x1A,           //+ "Wrong alliance for %s.";
    CHAT_INVALID_NAME_NOTICE          = 0x1B,           //+ "Invalid channel name";
    CHAT_NOT_MODERATED_NOTICE         = 0x1C,           //+ "%s is not moderated";
    CHAT_PLAYER_INVITED_NOTICE        = 0x1D,           //+ "[%s] You invited %s to join the channel";
    CHAT_PLAYER_INVITE_BANNED_NOTICE  = 0x1E,           //+ "[%s] %s has been banned.";
    CHAT_THROTTLED_NOTICE             = 0x1F,           //+ "[%s] The number of messages that can be sent to this channel is limited, please wait to send another message.";
    CHAT_NOT_IN_AREA_NOTICE           = 0x20,           //+ "[%s] You are not in the correct area for this channel."; -- The user is trying to send a chat to a zone specific channel, and they're not physically in that zone.
    CHAT_NOT_IN_LFG_NOTICE            = 0x21,           //+ "[%s] You must be queued in looking for group before joining this channel."; -- The user must be in the looking for group system to join LFG chat channels.
    CHAT_VOICE_ON_NOTICE              = 0x22,           //+ "[%s] Channel voice enabled by %s.";
    CHAT_VOICE_OFF_NOTICE             = 0x23            //+ "[%s] Channel voice disabled by %s.";
};

enum ChannelFlags
{
    CHANNEL_FLAG_NONE       = 0x00,
    CHANNEL_FLAG_CUSTOM     = 0x01,
    // 0x02
    CHANNEL_FLAG_TRADE      = 0x04,
    CHANNEL_FLAG_NOT_LFG    = 0x08,
    CHANNEL_FLAG_GENERAL    = 0x10,
    CHANNEL_FLAG_CITY       = 0x20,
    CHANNEL_FLAG_LFG        = 0x40,
    CHANNEL_FLAG_VOICE      = 0x80
    // General                  0x18 = 0x10 | 0x08
    // Trade                    0x3C = 0x20 | 0x10 | 0x08 | 0x04
    // LocalDefense             0x18 = 0x10 | 0x08
    // GuildRecruitment         0x38 = 0x20 | 0x10 | 0x08
    // LookingForGroup          0x50 = 0x40 | 0x10
};

enum ChannelDBCFlags
{
    CHANNEL_DBC_FLAG_NONE       = 0x00000,
    CHANNEL_DBC_FLAG_INITIAL    = 0x00001,              // General, Trade, LocalDefense, LFG
    CHANNEL_DBC_FLAG_ZONE_DEP   = 0x00002,              // General, Trade, LocalDefense, GuildRecruitment
    CHANNEL_DBC_FLAG_GLOBAL     = 0x00004,              // WorldDefense
    CHANNEL_DBC_FLAG_TRADE      = 0x00008,              // Trade, LFG
    CHANNEL_DBC_FLAG_CITY_ONLY  = 0x00010,              // Trade, GuildRecruitment, LFG
    CHANNEL_DBC_FLAG_CITY_ONLY2 = 0x00020,              // Trade, GuildRecruitment, LFG
    CHANNEL_DBC_FLAG_DEFENSE    = 0x10000,              // LocalDefense, WorldDefense
    CHANNEL_DBC_FLAG_GUILD_REQ  = 0x20000,              // GuildRecruitment
    CHANNEL_DBC_FLAG_LFG        = 0x40000,              // LFG
    CHANNEL_DBC_FLAG_UNK1       = 0x80000               // General
};

enum ChannelMemberFlags
{
    MEMBER_FLAG_NONE        = 0x00,
    MEMBER_FLAG_OWNER       = 0x01,
    MEMBER_FLAG_MODERATOR   = 0x02,
    MEMBER_FLAG_VOICED      = 0x04,
    MEMBER_FLAG_MUTED       = 0x08,
    MEMBER_FLAG_CUSTOM      = 0x10,
    MEMBER_FLAG_MIC_MUTED   = 0x20
    // 0x40
    // 0x80
};

class TC_GAME_API Channel
{
    struct PlayerInfo
    {
        uint8 flags;
        bool invisible;

        bool IsInvisible() const { return invisible; }
        void SetInvisible(bool on) { invisible = on; }

        bool HasFlag(uint8 flag) const { return (flags & flag) != 0; }
        void SetFlag(uint8 flag) { flags |= flag; }

        bool IsOwner() const { return (flags & MEMBER_FLAG_OWNER) != 0; }
        void SetOwner(bool state)
        {
            if (state) flags |= MEMBER_FLAG_OWNER;
            else flags &= ~MEMBER_FLAG_OWNER;
        }

        bool IsModerator() const { return (flags & MEMBER_FLAG_MODERATOR) != 0; }
        void SetModerator(bool state)
        {
            if (state) flags |= MEMBER_FLAG_MODERATOR;
            else flags &= ~MEMBER_FLAG_MODERATOR;
        }

        bool IsMuted() const { return (flags & MEMBER_FLAG_MUTED) != 0; }
        void SetMuted(bool state)
        {
            if (state) flags |= MEMBER_FLAG_MUTED;
            else flags &= ~MEMBER_FLAG_MUTED;
        }
    };

    public:
        Channel(std::string const& name, uint32 channel_id, uint32 team = 0);

        std::string const& GetName() const { return _channelName; }

        uint32 GetChannelId() const { return _channelId; }
        bool IsConstant() const { return _channelId != 0; }
        bool IsLFG() const { return (GetFlags() & CHANNEL_FLAG_LFG) != 0; }

        bool IsAnnounce() const { return _announceEnabled; }
        void SetAnnounce(bool nannounce) { _announceEnabled = nannounce; }

        std::string const& GetPassword() const { return _channelPassword; }
        void SetPassword(std::string const& npassword) { _channelPassword = npassword; }

        uint32 GetNumPlayers() const { return _playersStore.size(); }

        uint8 GetFlags() const { return _channelFlags; }
        bool HasFlag(uint8 flag) const { return (_channelFlags & flag) != 0; }

        void JoinChannel(Player* player, std::string const& pass);
        void LeaveChannel(Player* player, bool send = true);

        void KickOrBan(Player const* player, std::string const& badname, bool ban);
        void Kick(Player const* player, std::string const& badname) { KickOrBan(player, badname, false); }
        void Ban(Player const* player, std::string const& badname) { KickOrBan(player, badname, true); }

        void UnBan(Player const* player, std::string const& badname);
        void Password(Player const* player, std::string const& pass);
        void SetMode(Player const* player, std::string const& p2n, bool mod, bool set);

        void SetModerator(Player const* player, std::string const& newname) { SetMode(player, newname, true, true); }
        void UnsetModerator(Player const* player, std::string const& newname) { SetMode(player, newname, true, false); }
        void SetMute(Player const* player, std::string const& newname) { SetMode(player, newname, false, true); }
        void UnsetMute(Player const* player, std::string const& newname) { SetMode(player, newname, false, false); }

        void SetInvisible(Player const* player, bool on);

        void SetOwner(ObjectGuid guid, bool exclaim = true);
        void SetOwner(Player const* player, std::string const& name);
        void SendWhoOwner(ObjectGuid guid);

        void List(Player const* player) const;
        void Announce(Player const* player);
        void Say(ObjectGuid guid, std::string const& what, uint32 lang) const;
        void Invite(Player const* player, std::string const& newp);
        void Voice(ObjectGuid guid1, ObjectGuid guid2) const;
        void DeVoice(ObjectGuid guid1, ObjectGuid guid2) const;
        void JoinNotify(ObjectGuid guid) const;                                       // invisible notify
        void LeaveNotify(ObjectGuid guid) const;                                      // invisible notify
        void SetOwnership(bool ownership) { _ownershipEnabled = ownership; }
        static void CleanOldChannelsInDB();

    private:
        // initial packet data (notify type and channel name)
        void MakeNotifyPacket(WorldPacket* data, uint8 notify_type) const;
        // type specific packet data
        void MakeJoined(WorldPacket* data, ObjectGuid guid) const;                          //+ 0x00
        void MakeLeft(WorldPacket* data, ObjectGuid guid) const;                            //+ 0x01
        void MakeYouJoined(WorldPacket* data) const;                                        //+ 0x02
        void MakeYouLeft(WorldPacket* data) const;                                          //+ 0x03
        void MakeWrongPassword(WorldPacket* data) const;                                    //? 0x04
        void MakeNotMember(WorldPacket* data) const;                                        //? 0x05
        void MakeNotModerator(WorldPacket* data) const;                                     //? 0x06
        void MakePasswordChanged(WorldPacket* data, ObjectGuid guid) const;                 //+ 0x07
        void MakeOwnerChanged(WorldPacket* data, ObjectGuid guid) const;                    //? 0x08
        void MakePlayerNotFound(WorldPacket* data, std::string const& name) const;          //+ 0x09
        void MakeNotOwner(WorldPacket* data) const;                                         //? 0x0A
        void MakeChannelOwner(WorldPacket* data) const;                                     //? 0x0B
        void MakeModeChange(WorldPacket* data, ObjectGuid guid, uint8 oldflags) const;      //+ 0x0C
        void MakeAnnouncementsOn(WorldPacket* data, ObjectGuid guid) const;                 //+ 0x0D
        void MakeAnnouncementsOff(WorldPacket* data, ObjectGuid guid) const;                //+ 0x0E
        void MakeMuted(WorldPacket* data) const;                                            //? 0x11
        void MakePlayerKicked(WorldPacket* data, ObjectGuid bad, ObjectGuid good) const;    //? 0x12
        void MakeBanned(WorldPacket* data) const;                                           //? 0x13
        void MakePlayerBanned(WorldPacket* data, ObjectGuid bad, ObjectGuid good) const;    //? 0x14
        void MakePlayerUnbanned(WorldPacket* data, ObjectGuid bad, ObjectGuid good) const;  //? 0x15
        void MakePlayerNotBanned(WorldPacket* data, std::string const& name) const;         //? 0x16
        void MakePlayerAlreadyMember(WorldPacket* data, ObjectGuid guid) const;             //+ 0x17
        void MakeInvite(WorldPacket* data, ObjectGuid guid) const;                          //? 0x18
        void MakeInviteWrongFaction(WorldPacket* data) const;                               //? 0x19
        void MakeWrongFaction(WorldPacket* data) const;                                     //? 0x1A
        void MakeInvalidName(WorldPacket* data) const;                                      //? 0x1B
        void MakeNotModerated(WorldPacket* data) const;                                     //? 0x1C
        void MakePlayerInvited(WorldPacket* data, std::string const& name) const;           //+ 0x1D
        void MakePlayerInviteBanned(WorldPacket* data, std::string const& name) const;      //? 0x1E
        void MakeThrottled(WorldPacket* data) const;                                        //? 0x1F
        void MakeNotInArea(WorldPacket* data) const;                                        //? 0x20
        void MakeNotInLfg(WorldPacket* data) const;                                         //? 0x21
        void MakeVoiceOn(WorldPacket* data, ObjectGuid guid) const;                         //+ 0x22
        void MakeVoiceOff(WorldPacket* data, ObjectGuid guid) const;                        //+ 0x23

        void SendToAll(WorldPacket* data, ObjectGuid guid = ObjectGuid::Empty) const;
        void SendToAllButOne(WorldPacket* data, ObjectGuid who) const;
        void SendToOne(WorldPacket* data, ObjectGuid who) const;

        bool IsOn(ObjectGuid who) const { return _playersStore.count(who) != 0; }
        bool IsBanned(ObjectGuid guid) const { return _bannedStore.count(guid) != 0; }

        void UpdateChannelInDB() const;
        void UpdateChannelUseageInDB() const;

        uint8 GetPlayerFlags(ObjectGuid guid) const
        {
            PlayerContainer::const_iterator itr = _playersStore.find(guid);
            return itr != _playersStore.end() ? itr->second.flags : 0;
        }

        void SetModerator(ObjectGuid guid, bool set)
        {
            if (!IsOn(guid))
                return;

            PlayerInfo& playerInfo = _playersStore.at(guid);
            if (playerInfo.IsModerator() != set)
            {
                uint8 oldFlag = GetPlayerFlags(guid);
                playerInfo.SetModerator(set);

                WorldPacket data;
                MakeModeChange(&data, guid, oldFlag);
                SendToAll(&data);
            }
        }

        void SetMute(ObjectGuid guid, bool set)
        {
            if (!IsOn(guid))
                return;

            PlayerInfo& playerInfo = _playersStore.at(guid);
            if (playerInfo.IsMuted() != set)
            {
                uint8 oldFlag = GetPlayerFlags(guid);
                playerInfo.SetMuted(set);

                WorldPacket data;
                MakeModeChange(&data, guid, oldFlag);
                SendToAll(&data);
            }
        }

        typedef std::map<ObjectGuid, PlayerInfo> PlayerContainer;
        typedef GuidUnorderedSet BannedContainer;

        bool _announceEnabled;          //< Whether we should broadcast a packet whenever a player joins/exits the channel
        bool _ownershipEnabled;         //< Whether the channel has to maintain an owner
        bool _persistentChannel;        //< Whether the channel is saved to DB
        bool _isOwnerInvisible;         //< Whether the channel is owned by invisible GM, ownership should change to first player that joins channel

        uint8 _channelFlags;
        uint32 _channelId;
        uint32 _channelTeam;
        ObjectGuid _ownerGuid;
        std::string _channelName;
        std::string _channelPassword;
        PlayerContainer _playersStore;
        BannedContainer _bannedStore;
};
#endif

