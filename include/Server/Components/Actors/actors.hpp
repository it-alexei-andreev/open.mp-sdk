#pragma once

#include <anim.hpp>
#include <component.hpp>
#include <player.hpp>
#include <types.hpp>
#include <values.hpp>

struct ActorSpawnData
{
	Vector3 position;
	float facingAngle;
	int skin;
};

/// Actor interace
struct IActor : public IExtensible, public IEntity
{
	/// Sets the actor's name
	virtual void setName(StringView name) = 0;

	/// Sets the actor's name for player
	virtual void setNameForPlayer(StringView name, IPlayer& player) = 0;

	/// Gets the actor's name
	virtual StringView getName() = 0;

	/// Sets the actor's skin
	virtual void setSkin(int id) = 0;

	/// Gets the actor's model
	virtual int getSkin() const = 0;

	/// Set the actor's armour
	virtual void setArmour(float armour) = 0;

	/// Set the actor's armour for player
	virtual void setArmourForPlayer(float armour, IPlayer& player) = 0;

	/// Get the actor's armour
	virtual float getArmour() const = 0;

	/// Sets the actor's armed weapon
	virtual void setWeapon(uint32_t weapon) = 0;

	/// Sets the actor's armed weapon for player
	virtual void setWeaponForPlayer(uint32_t weapon, IPlayer& player) = 0;

	/// Gets the actor's armed weapon
	virtual uint32_t getWeapon() const = 0;

	/// Sets actor to aim into position
	virtual void setAim(Vector3 position, int time) = 0;

	/// Sets the actor's position with normilization of Z vector
	virtual void setPositionFindZ(Vector3 position) = 0;

	/// Update actor position without restream
	virtual void updatePosition(Vector3 position) = 0;

	/// Apply an animation for the actor
	virtual void applyAnimation(const AnimationData& animation) = 0;

	/// Get the actor's applied animation
	virtual const AnimationData& getAnimation() const = 0;

	/// Clear the actor's animations
	virtual void clearAnimations() = 0;

	/// Put actor in the vehicle
	virtual void putInVehicle(IVehicle& vehicle, int seat, bool force) = 0;

	/// Put actor in the vehicle
	virtual void removeFromVehicle(bool force) = 0;

	/// Get actor's vehicle
	virtual int getVehicle() = 0;

	/// Get actor's vehicle seat
	virtual int getSeat() = 0;

	/// Set the actor's health
	virtual void setHealth(float health) = 0;

	/// Get the actor's health
	virtual float getHealth() const = 0;

	/// Set whether the actor is invulnerable
	virtual void setInvulnerable(bool invuln) = 0;

	/// Get whether the actor is invulnerable
	virtual bool isInvulnerable() const = 0;

	/// Checks if actor is streamed for a player
	virtual bool isStreamedInForPlayer(const IPlayer& player) const = 0;

	/// Streams actor for a player
	virtual void streamInForPlayer(IPlayer& player) = 0;

	/// Streams out actor for a player
	virtual void streamOutForPlayer(IPlayer& player) = 0;

	/// Get actor spawn data
	virtual const ActorSpawnData& getSpawnData() = 0;
};

struct ActorEventHandler
{
	virtual void onPlayerGiveDamageActor(IPlayer& player, IActor& actor, float amount, unsigned weapon, BodyPart part) { }
	virtual void onActorStreamOut(IActor& actor, IPlayer& forPlayer) { }
	virtual void onActorStreamIn(IActor& actor, IPlayer& forPlayer) { }
};

static const UID ActorsComponent_UID = UID(0xc81ca021eae2ad5c);
struct IActorsComponent : public IPoolComponent<IActor>
{
	PROVIDE_UID(ActorsComponent_UID);

	/// Get the ActorEventHandler event dispatcher
	virtual IEventDispatcher<ActorEventHandler>& getEventDispatcher() = 0;

	/// Create an actor
	virtual IActor* create(int skin, Vector3 pos, float angle) = 0;
};
