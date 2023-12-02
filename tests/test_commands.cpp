#include <catch2/catch_test_macros.hpp>
#include "../shared_src/protocol.h"
#include "../shared_src/socket.h"
#include "../game_src/constants_game.h"
#include "../game_src/commands/command.h"
#include "../game_src/commands/hit_upclose.h"
#include "../game_src/commands/jump.h"
#include "../game_src/commands/launch_bazooka.h"
#include "../game_src/commands/match_command.h"
#include "../game_src/commands/move.h"
#include "../game_src/commands/throw_grenade.h"
#include "../game_src/commands/remote_operated.h"


Socket mockServerS3("1232");
Protocol mockClient3("localhost", "1232");
Socket peer3 = mockServerS3.accept();
Protocol mockServer3(std::move(peer3));

TEST_CASE("Sending and receiving Command Move", "[info]") {

    int wormdIDSent = 2;
    int dirSent = 0;

    Move* move = new Move(wormdIDSent, dirSent);

    move->send(mockClient3);

    std::shared_ptr<Command>commandReceived(mockServer3.receiveCommand());
    std::shared_ptr<Move> moveReceived = std::dynamic_pointer_cast<Move>(commandReceived);

    REQUIRE(moveReceived->getID() == move->getID());
    REQUIRE(moveReceived->getDir() == move->getDir());
}

TEST_CASE("Sending and receiving Command Jump", "[info]") {

    int wormdIDSent = 2;
    int dirSent = 0;

    Jump* jump = new Jump(wormdIDSent, dirSent);

    jump->send(mockClient3);

    std::shared_ptr<Command>commandReceived(mockServer3.receiveCommand());
    std::shared_ptr<Jump> jumpReceived = std::dynamic_pointer_cast<Jump>(commandReceived);

    REQUIRE(jumpReceived->getID() == jump->getID());
    REQUIRE(jumpReceived->getDir() == jump->getDir());
}

TEST_CASE("Sending and receiving Command HitUpclose", "[info]") {

    int wormdIDSent = 2;
    int dirSent = 0;

    HitUpclose* hitUpClose = new HitUpclose(wormdIDSent, dirSent);

    hitUpClose->send(mockClient3);

    std::shared_ptr<Command>commandReceived(mockServer3.receiveCommand());
    std::shared_ptr<HitUpclose> hitUpCloseReceived = std::dynamic_pointer_cast<HitUpclose>(commandReceived);

    REQUIRE(hitUpCloseReceived->getID() == hitUpClose->getID());
    REQUIRE(hitUpCloseReceived->getDir() == hitUpClose->getDir());
}

TEST_CASE("Sending and receiving Command RemoteOperated", "[info]") {

    int wormdIDSent = 2;
    Position pos(1.3,-6.147);

    RemoteOperated* teleport = new RemoteOperated(wormdIDSent, REMOTE_OPERATED, pos);

    teleport->send(mockClient3);

    std::shared_ptr<Command>commandReceived(mockServer3.receiveCommand());
    std::shared_ptr<RemoteOperated> teleportReceived = std::dynamic_pointer_cast<RemoteOperated>(commandReceived);

    REQUIRE(teleportReceived->getID() == teleport->getID());
    REQUIRE(teleportReceived->getX() == teleport->getX());
    REQUIRE(teleportReceived->getY() == teleport->getY());
}

TEST_CASE("Sending and receiving Command LaunchRocket", "[info]") {

    int wormdIDSent = 2;
    int type = 0;
    int dirSent = 0;
    float angle = 12.65;
    float power = 0.3695;

    LaunchRocket* launchRocket = new LaunchRocket(type, wormdIDSent, dirSent, angle, power);

    launchRocket->send(mockClient3);

    std::shared_ptr<Command>commandReceived(mockServer3.receiveCommand());
    std::shared_ptr<LaunchRocket> launchRocketReceived = std::dynamic_pointer_cast<LaunchRocket>(commandReceived);

    REQUIRE(launchRocketReceived->getID() == launchRocket->getID());
    REQUIRE(launchRocketReceived->getType() == launchRocket->getType());
    REQUIRE(launchRocketReceived->getDir() == launchRocket->getDir());
    REQUIRE(launchRocketReceived->getAngle() == launchRocket->getAngle());
    REQUIRE(launchRocketReceived->getPower() == launchRocket->getPower());
}

TEST_CASE("Sending and receiving Command ThrowGrenade", "[info]") {

    int wormdIDSent = 2;
    int type = 0;
    int dirSent = 0;
    float angle = 12.65;
    float power = 0.3695;
    int timer = 3;

    ThrowGrenade* throwGrenade = new ThrowGrenade(type, wormdIDSent, dirSent, angle, power, 3);

    throwGrenade->send(mockClient3);

    std::shared_ptr<Command>commandReceived(mockServer3.receiveCommand());
    std::shared_ptr<ThrowGrenade> throwGrenadeReceived = std::dynamic_pointer_cast<ThrowGrenade>(commandReceived);

    REQUIRE(throwGrenadeReceived->getID() == throwGrenade->getID());
    REQUIRE(throwGrenadeReceived->getType() == throwGrenade->getType());
    REQUIRE(throwGrenadeReceived->getDir() == throwGrenade->getDir());
    REQUIRE(throwGrenadeReceived->getAngle() == throwGrenade->getAngle());
    REQUIRE(throwGrenadeReceived->getPower() == throwGrenade->getPower());
    REQUIRE(throwGrenadeReceived->getTimer() == throwGrenade->getTimer());
}
