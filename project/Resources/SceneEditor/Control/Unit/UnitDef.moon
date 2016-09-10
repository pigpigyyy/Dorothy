import Struct from require "Lib.Utils"

{
	Unit:Struct.Data.Unit {
		-- Character Settings
		"name","tag","model",
		"size","scale","maxHp",
		"move","jump","actions",
		-- Physics Settings
		"type","density","friction",
		"restitution","fixedRotation","isBullet",
		"linearDamping","angularDamping","gravityScale",
		-- Battle Settings
		"attackBase","attackPower","attackRange",
		"attackTarget","targetAllow","attackDelay",
		"attackType","usePreciseHit","bulletType",
		"damageType","defenceType",
		-- AI Settings
		"sensity","detectDistance","reflexArc",
		"instincts",
		-- Visual Settings
		"attackEffect","attackEffectDelay","hitEffect",
		"sndAttack","sndDeath",
	}

	UnitGroup:Struct.Data.UnitGroup "name","units"
}