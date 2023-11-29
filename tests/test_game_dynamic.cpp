// #include <catch2/catch_test_macros.hpp>
// #include <iostream>
// #include <vector>
// #include "../shared_src/protocol.h"
// #include "../shared_src/socket.h"
// #include "../game_src/beam_dto.h"
// #include "../game_src/worm_dto.h"
// #include "../game_src/game_map.h"
// #include "../game_src/serializable.h"


// Socket mockServerS("1234");
// Protocol mockClient("localhost", "1234");
// Socket peer = mockServerS.accept();
// Protocol mockServer(std::move(peer));

// std::string mapName = "small";
// int numTeams = 2;
// std::vector<BeamDTO> beams;
// std::vector<WormDTO> worms;

// TEST_CASE("Sending and receiving a GameDynamic") {

//     Position pos(9.7, 11.0);
//     Position pos2(9.89, 9.1);

//     worms.push_back(WormDTO(2, 0, 1, 100, 0.9, 4.0, 1, pos, {}));
//     worms.push_back(WormDTO(1, 1, 2,  0, 0.0, 0.333, 0, pos2, {}));

//     beams.push_back(BeamDTO(6, Position(10.0f, 10.0f), 0));
//     beams.push_back(BeamDTO(3, Position(16.0f, 8.0f), 0));
//     beams.push_back(BeamDTO(3, Position(16.0f, 25.0f), 0));

// }