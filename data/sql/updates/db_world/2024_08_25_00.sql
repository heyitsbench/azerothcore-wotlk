-- DB update 2024_08_22_01 -> 2024_08_25_00
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=23569;
DELETE FROM `smart_scripts` WHERE `entryorguid`=23569 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2356900 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(23569,0,0,1,62,0,100,0,8837,0,0,0,134,42670,0,0,0,0,0,7,0,0,0,0,0,0,0,'Renn McGill - On Gossip Option 0 Selected - Invoker Cast \'Replace Repaired Diving Gear\''),
(23569,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Renn McGill - On Gossip Option 0 Selected - Close Gossip'),
(23569,0,2,0,20,0,100,0,11140,0,0,0,80,2356900,0,0,0,0,0,1,0,0,0,0,0,0,0,'Renn McGill - On Quest \'Recover the Cargo!\' Finished - Run Script'),
(2356900,9,0,0,0,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Renn McGill - On Script - Remove Npc Flag Questgiver+Gossip'),
(2356900,9,1,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Renn McGill - On Script - Say Line 0'),
(2356900,9,2,0,0,0,100,0,4000,4000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Renn McGill - On Script - Say Line 1'),
(2356900,9,3,0,0,0,100,0,5000,5000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Renn McGill - On Script - Say Line 2'),
(2356900,9,4,0,0,0,100,0,6000,6000,0,0,82,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Renn McGill - On Script - Add Npc Flag Questgiver+Gossip');
