#include "battlestate.hpp"

//Con-/Destructors
BattleState::BattleState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states, ScoreManager* scoreManager)
    : State(font, mousePosView, states, scoreManager){
    this->font = font;
    this->mousePosView = mousePosView;
    this->scoreManager = scoreManager;
    this->states = states;
    this->infoText.setString("An Enemy approaches");

    std::cout <<"BattleState Here" <<std::endl;

    initTextures();
    initEntities();

    if(!this->bgTexture.loadFromFile("assets/prototype_background_big.png"))
        std::printf("ERROR BG TEXTURE NOT LOADED IN MENU!\n");

    this->bg.setTexture(this->bgTexture);
    this->bg.setScale(sf::Vector2f(0.8,0.8));
    this->bg.setPosition(sf::Vector2f(0,-300));

    this->overlayBg.setFillColor(sf::Color(0,0,0,200));
    this->overlayBg.setSize(sf::Vector2f(1280, 100));
    this->overlayBg.setPosition(sf::Vector2f(0,0));


    this->attackButton.defineAll(1280.0/2, 720.0-100, 150, 50, "Attack", font, true);
    this->healButton.defineAll(1280.0/2 + 225, 720.0-100, 150, 50, "Heal", font, true);
    this->quitButton.defineAll(1280.0/2 + 450, 720.0-100, 150, 50, "Quit", font, true);


    this->initStatInfo();
    this->scoreText.setFont(*this->font);
    this->scoreText.setCharacterSize(35);
    this->scoreText.setString(scoreStream.str());
    this->scoreText.setPosition(1280.0/3 * 2 + 200, 10.0);

    this->roundText.setFont(*this->font);
    this->roundText.setCharacterSize(35);
    this->roundText.setString(roundStream.str());
    this->roundText.setPosition(50 , 10.0);

    this->infoText.setFont(*this->font);
    this->infoText.setCharacterSize(35);
    this->infoText.setPosition( 50, 720.0/4 * 3 + 50);

    this->wonText.setFont(*this->font);
    this->wonText.setCharacterSize(45);
    this->wonText.setPosition( 1280.0/2 - 100, 720.0/4 - 150);
    this->wonText.setString(" ");



}

BattleState::~BattleState()= default;

//Functions


void BattleState::update() {
    //Update Mouse Position
    this->attackButton.update(*mousePosView);
    this->healButton.update(*mousePosView);
    this->quitButton.update(*mousePosView);
    this->continueButton.update(*mousePosView);
    this->exitButton.update(*mousePosView);

    this->battle();



}

void BattleState::render(sf::RenderWindow& renderWindow) {
    renderWindow.draw(this->bg);
    renderWindow.draw(this->overlayBg);
    attackButton.render(renderWindow);
    healButton.render(renderWindow);
    quitButton.render(renderWindow);
    this->player.render(renderWindow);
    this->enemy.render(renderWindow);

    renderWindow.draw(statInfoE);
    renderWindow.draw(statInfoP);
    renderWindow.draw(scoreText);
    renderWindow.draw(roundText);
    renderWindow.draw(infoText);


    if(isPaused){
        renderWindow.draw(pauseBg);
        continueButton.render(renderWindow);
        exitButton.render(renderWindow);
        renderWindow.draw(wonText);

    }


}

void BattleState::endState() {
    // LATER: add score to list here
    std::cout <<"Ending BattleState" <<std::endl;
    this->scoreManager->updateScores(scoreCount);
}

void BattleState::initTextures() {

    if(!this->textures["PLAYER"].loadFromFile("assets/placeholder.png"))
        std::printf("ERROR PLAYER TEXTURE NOT LOADED IN!\n");

}

void BattleState::initEntities() {
    this->player.createSprite(&textures["PLAYER"], 0.7, 0.7);
    this->player.setPosition(1280.0/2 + 100,175);
    this->player.createStatsComponent(1, rd);

    this->spawnEnemy();
    std::cout << "PLAYER" << std::endl;
    this->player.update();
    std::cout << "ENEMY" << std::endl;
    this->enemy.update();

    this->setInitiative();


}

void BattleState::spawnEnemy() {
    this->enemy.createSprite(&textures["PLAYER"], -0.7, 0.7 );
    this->enemy.setPosition(1280.0/2 - 100,175);
    this->enemy.createStatsComponent(1, rd);
}

void BattleState::battle() {

    if(this->player.statsComponent->hasTurn){
        this->playerTurn();

    }
    else
        this->enemyTurn();


}

void BattleState::setInitiative()  {
    if(this->player.statsComponent->speed >= this->enemy.statsComponent->speed ) {
        player.statsComponent->hasTurn = true;
        infoText.setString("You start");
        std::cout << "PLAYER starts." << std::endl;

    }
    else{
        enemy.statsComponent->hasTurn = true;
        std::cout << "ENEMY starts" << std::endl;
        infoText.setString("The enemy starts.");
    }


}


void BattleState::playerTurn(){
    using namespace std::chrono_literals;
    updateUI();

            //Attack
            if (attackButton.isClicked()) {
                this->player.statsComponent->hasTurn = false;
                infoText.setString("You attack the enemy!");
                updateUI();
                std::this_thread::sleep_for(0.5s);
                this->player.statsComponent->attack(&enemy);

                if(this->enemy.statsComponent->hp <= 0)
                    this->battleWon();

                else {

                    this->enemy.statsComponent->hasTurn = true;
                }
                updateUI();
                ++this->scoreCount;



            }
            //Heal
            if (healButton.isClicked()) {
                this->player.statsComponent->hasTurn = false;
                infoText.setString("You fully heal yourself.");
                updateUI();
                std::this_thread::sleep_for(0.5s);
                if(this->player.statsComponent->hp < this->player.statsComponent->hpMax
                   && this->player.statsComponent->heals > 0){
                    this->player.statsComponent->heal();
                }

                this->enemy.statsComponent->hasTurn = true;
                ++this->scoreCount;
                updateUI();

            }
            //Quit
            if (quitButton.isClicked()) {
                quit();
            }
            /*--------------isPaused------------------------*/
            //Continue
            if (continueButton.isClicked()) {
                std::cout << "Battle continues" << std::endl;
                updateUI();
                this->enemy.respawn(this->player.statsComponent->level, rd , &player);
                this->continueButton.setActivity(false);
                this->exitButton.setActivity(false);
                this->isPaused = false;
                ++this->roundCount;
                updateUI();

                this->setInitiative();
                std::this_thread::sleep_for(0.5s);
                this->attackButton.setActivity(true);
                this->healButton.setActivity(true);
                this->quitButton.setActivity(true);

            }
            //Exit
            if (exitButton.isClicked()) {
                this->quit();
            }


}


void BattleState::enemyTurn(){
    using namespace std::chrono_literals;
    std::uniform_int_distribution<int> distLow(0,2);

    if(this->enemy.statsComponent->hasTurn){
        std::cout << "ENEMY approaches" << std::endl;
        this->infoText.setString("It's the enemy's turn");
        updateUI();
        std::this_thread::sleep_for(0.5s);

        switch(distLow(rd)) {
            case PASS:
                std::cout << "ENEMY passes" << std::endl;
                this->infoText.setString("The enemy stares at you, menacingly.");
                updateUI();
                std::this_thread::sleep_for(0.5s);
                this->player.statsComponent->hasTurn = true;
                this->enemy.statsComponent->hasTurn = false;
                break;

            case HEAL:
                std::cout << "ENEMY heals" << std::endl;
                this->infoText.setString("The enemy tries to heal themselves.\nBut nothing happened");
                updateUI();

                if (this->enemy.statsComponent->hp < this->enemy.statsComponent->hpMax
                    && this->enemy.statsComponent->heals > 0) {
                    this->enemy.statsComponent->heal();
                    this->infoText.setString("The enemy heals themselves.");
                    updateUI();
                }

                std::this_thread::sleep_for(0.5s);
                this->enemy.statsComponent->hasTurn = false;
                this->player.statsComponent->hasTurn = true;
                break;

            case ATTACK:
                std::cout << "Enemy attacks" << std::endl;
                this->infoText.setString("The enemy attacks you!");
                updateUI();

                this->enemy.statsComponent->attack(&player);

                if (this->player.statsComponent->hp <= 0)
                    this->battleLost();

                else{
                    this->enemy.statsComponent->hasTurn = false;
                    this->player.statsComponent->hasTurn = true;
                }
                std::this_thread::sleep_for(0.5s);

                break;
        }
        updateUI();
    }
}


void BattleState::battleLost() {
    infoText.setString("You lost.");
    updateUI();
    enemy.statsComponent->hasTurn = false;
    this->attackButton.setActivity(false);
    this->healButton.setActivity(false);
    player.statsComponent->hasTurn = true;

}

void BattleState::battleWon() {
    using namespace std::chrono_literals;
    updateUI();
    this->scoreCount =  this->scoreCount + 100;
    this->wonText.setString("You won! \n" + scoreStream.str());
    updateUI();

    //Stop Battle
    this->attackButton.setActivity(false);
    this->healButton.setActivity(false);
    this->quitButton.setActivity(false);
    this->isPaused = true;
    this->player.statsComponent->hasTurn = true;
    this->enemy.statsComponent->hasTurn = false;

    //Init Screen
    this->pauseBg.setSize(sf::Vector2f(1280,720));
    this->pauseBg.setFillColor(sf::Color(0,0,0,230));
    this->continueButton.defineAll(1280.0/2 - 100, 720.0/2-150, 200, 50, "Continue", font, true);
    this->exitButton.defineAll(1280.0/2 - 100, 720.0/2, 200, 50, "Quit", font, true);



    //Button logic
    std::this_thread::sleep_for(0.5s);
    this->continueButton.setActivity(true);
    this->exitButton.setActivity(true);


}

void BattleState::initStatInfo() {
    this->scoreStream << "Score: " << this->scoreCount;
    this->roundStream << "Round: " << this->roundCount;

    this->pStats << "PLAYER LV: " << this->player.statsComponent->level << "\n"
                 << "HEALTH: " << this->player.statsComponent->hp << " / "<<  this->player.statsComponent->hpMax << "\n"
                 << "HEALS: " << this->player.statsComponent->heals << " / " << "3";

    this->eStats << "ENEMY LV: " << this->enemy.statsComponent->level << "\n"
                 << "HEALTH: " << this->enemy.statsComponent->hp << " / "<<  this->enemy.statsComponent->hpMax << "\n"
                 << "HEALS: " << this->enemy.statsComponent->heals << " / " << "3";

    // NOTED SIDE POSITION  (1280.0/4 - 200, 720.0/4 * 3 + 20)

    this->statInfoP.setFont(*font);
    this->statInfoP.setCharacterSize(25);
    this->statInfoP.setString(pStats.str());
    this->statInfoP.setPosition(1280.0/4 * 2 -50, 10);

    this->statInfoE.setFont(*font);
    this->statInfoE.setCharacterSize(25);
    this->statInfoE.setString(eStats.str());
    this->statInfoE.setPosition(1280.0/4 * 1 - 50, 10);

}

void BattleState::updateStatInfo() {
    this->pStats.str(std::string());
    this->eStats.str(std::string());


    this->pStats << "PLAYER LV: " << this->player.statsComponent->level << "\n"
                 << "HEALTH: " << this->player.statsComponent->hp << " / "<<  this->player.statsComponent->hpMax << "\n"
                 << "HEALS: " << this->player.statsComponent->heals << " / " << "3";

    this->eStats << "ENEMY LV: " << this->enemy.statsComponent->level << "\n"
                 << "HEALTH: " << this->enemy.statsComponent->hp << " / "<<  this->enemy.statsComponent->hpMax << "\n"
                 << "HEALS: " << this->enemy.statsComponent->heals << " / " << "3";

    this->statInfoP.setString(pStats.str());
    this->statInfoE.setString(eStats.str());

}

void BattleState::updateUI() {
    // Update Score
    this->scoreStream.str(std::string());
    this->scoreStream << "Score: " << this->scoreCount;
    this->scoreText.setString(scoreStream.str());

    // Update Turn
    this->roundStream.str(std::string());
    this->roundStream << "Round: " << this->roundCount;
    this->roundText.setString(roundStream.str());
    ;

    updateStatInfo();





}
