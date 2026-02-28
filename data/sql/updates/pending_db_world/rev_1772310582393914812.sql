-- Fingers of Frost buff: change SpellPhaseMask from 3 (CAST|HIT) to 1 (CAST only).
-- With !IsTriggered() removed from CAST proc blocks, triggered spells now fire
-- CAST procs, so HIT phase is no longer needed for triggered spell consumption.
UPDATE `spell_proc` SET `SpellPhaseMask` = 1 WHERE `SpellId` = 74396;
