# Games
Games made in Video Game Development

A class at USC called Video Game Development teaching gaming using some libraries like GLEW and SDL in C++. Games include Asteroids and a Tower Defense game.

Skeleton code is provided for me in the class. This readme serves as a summary of what I worked on.
Though I only list the headers I created in full, the work I have done is not limited to those files since many objects interact with each other.

# Asteroids

List of headers that I created in full:
<ul>
  <li> AudioComponent.h </il>
  <li> CollisionComponent.h </il>
  <li> Laser.h </il>
  <li> MeshComponent.h </il>
  <li> MoveComponent.h </il>
  <li> Asteroid.h </il>
  <li> Ship.h </il>
  <li> Sound.h </il>
  <li> SphereCollision.h </il>
  <li> SpriteComponent.h </il>
  <li> InputComponent.h </il>
</ul>

Open the Xcode file and press build to play the game.

Controls:
<ul>
  <li> W: Move forward </li>
  <li> S: Move backward </li>
  <li> A: Rotate left </li>
  <li> D: Rotate right </li>
  <li> ESC: Quit  </li>
</ul>

# Tower Defense

List of headers I created in full:
<ul>
  <li> All the header files duplicated in Asteroids (Laser.h, Ship.h and Asteroid.h were not carried over) </il>
  <li> CannonBall.h </il>
  <li> Enemy.h </il>
  <li> GameMode.h </il>
  <li> HUD.h </il>
  <li> NavWorld.h </il>
  <li> NavComponent.h </il>
  <li> PathNode.h </il>
  <li> Spawner.h </il>
  <li> Tower.h </il>
  <li> FrostTower.h </il>
  <li> CannonTower.h </il>
</ul>

Open the Xcode file and press build to play the game.

NOTE: Make sure that the parent directories do not have whitespace in their names.

Controls:
<ul>
  <li> Click on a valid square and press 1 or 2 to build a tower. </il>
  <li> 1: Build a cannon tower </il>
  <li> 2: Build a frost tower </il>
  <li> ESC: Quit </il>
</ul>

# Space Racer
List of headers I created in full:
<ul>
  <li> All the header files duplicated in Tower Defense and/or Asteroids </il>
  <li> Arrow.h </il>
  <li> Checkpoint.h </il>
  <li> CameraComponent.h </il>
</ul>

Open the Xcode file and press build to play the game.

NOTE: Make sure that the parent directories do not have whitespace in their names.

Controls:
<ul>
  <li> W: Rotate upward </li>
  <li> S: Rotate downward </li>
  <li> A: Rotate leftward </li>
  <li> D: Rotate rightward </li>
  <li> P: Move forward </li>
  <li> ;: Move backward </li>
  <li> ESC: Quit </li>
</ul>

# Super Dance Battle Extreme

This was our final project for the class. Made in a team of three using the Unreal Editor so in order to open and run the game, you'll need Unreal Editor 4. Unreal Editor 4 has a nice blueprint system that emulates code functions. I used these in conjunction with C++ classes to make the game.
The game is a take to combine two classic games and put them together: Street Fighter and Dance Dance Revolution. The project was thus divided into two parts, the fighting element and the rhythm element. My responsibilities leaned to the rhythm aspect of the game as well as UI and HUD elements. For instance:
<ul>
  <li> I made the main menu which dynamically creates UI elements based on the Songs.txt in the /Content/Songs/ directory. </li>
  <li> With my teammates, we devised a way to parse the text file and create 'beats' in-game. </li>
  <li> I edited the songs, created the text files in the /Content/BeatMaps/ directory, syncing the numbers with specific beats in the song. </li>
  <li> I helped rework a lot of the code in SDBXGameMode.h, BeatSpawner.h, and SDBXGameInstance.h in the /Source/SDBX/ directory </li>
</ul>

To play the game:
Open SDBX.xcodepoj with Xcode. Build with target as SDBXEditor to open Unreal Editor. Press the play button in Unreal to play the game.
The game is a two player game and can be played with XBox controllers or on the keyboard.

Controls:
<ul>
  <li> A/D: P1 move left and right </li>
  <li> W: P1 jump </li>
  <li> F: P1 punch </li>
  <li> G: P1 dance </li>
  <li> H: P1 block </li>
  <li> Left/right arrows: P2 move left and right </li>
  <li> Up arrow: P2 jump </li>
  <li> P: P2 Punch </li>
  <li> [: P2 Dance </li>
  <li> ]: P2 Block </li>
</ul>
