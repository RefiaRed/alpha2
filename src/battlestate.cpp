#include "battlestate.hpp"

//Con-/Destructors
BattleState::BattleState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states, ScoreManager* scoreManager)
    : State(font, mousePosView, states, scoreManager){
    this->font = font;
    this->mousePosView = mousePosView;
    this->scoreManager = scoreManager;
    this->states = states;
    this->infoText.setString("An Enemy approaches");

    initTextures();
    initEntities();

    this->bg.setTexture(this->bgTexture);
    this->bg.setScale(sf::Vector2f(0.8,0.8));
    this->bg.setPosition(sf::Vector2f(0,-300));

    initUI();

}

BattleState::~BattleState()= default;

//Inits
void BattleState::initText() {
    initStatInfo();
    scoreText.setFont(*font);
    scoreText.setCharacterSize(35);
    scoreText.setString(scoreStream.str());
    scoreText.setPosition(1280.0/3 * 2 + 200, 10.0);

    roundText.setFont(*font);
    roundText.setCharacterSize(35);
    roundText.setString(roundStream.str());
    roundText.setPosition(50 , 10.0);

    infoText.setFont(*font);
    infoText.setCharacterSize(35);
    infoText.setPosition( 50, 720.0/4 * 3 + 50);

    wonText.setFont(*font);
    wonText.setCharacterSize(45);
    wonText.setPosition( 1280.0/2 - 100, 720.0/4 - 150);
    wonText.setString(" ");
}

void BattleState::initUI() {


    this->overlayBg.setFillColor(sf::Color(0,0,0,200));
    this->overlayBg.setSize(sf::Vector2f(1280, 100));
    this->overlayBg.setPosition(sf::Vector2f(0,0));


    this->attackButton.defineAll(1280.0/2, 720.0-100, 150, 50, "Attack", font, true);
    this->healButton.defineAll(1280.0/2 + 225, 720.0-100, 150, 50, "Heal", font, true);
    this->quitButton.defineAll(1280.0/2 + 450, 720.0-100, 150, 50, "Quit", font, true);

    initText();
}

void BattleState::initStatInfo() {
    this->scoreStream << "Score: " << this->scoreCount;
    this->roundStream << "Round: " << this->roundCount;

    this->pStats << "PLAYER LV: " << this->player.statsComponent->level << "\n"
                 << "HEALTH: " << this->player.statsComponent->hp << " / " <<  this->player.statsComponent->hpMax
                 << "   HEALS: " << this->player.statsComponent->heals << " / " << "3" << "\n"
                 <<"ATK: " << this->player.statsComponent->atk
                 << "   DEF: " << this->player.statsComponent->def;

    this->eStats << "ENEMY LV: " << this->enemy.statsComponent->level << "\n"
                 << "HEALTH: " << this->enemy.statsComponent->hp << " / "<<  this->enemy.statsComponent->hpMax
                 << "   HEALS: " << this->enemy.statsComponent->heals << " / " << "3" << "\n"
                 << "ATK: " << this->enemy.statsComponent->atk
                 << "    DEF: " << this->enemy.statsComponent->def;

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

void BattleState::initTextures() {

    if(!this->textures["PLAYER"].loadFromFile("assets/char1_idle.png"))
        std::printf("ERROR PLAYER TEXTURE NOT LOADED IN!\n");
    if(!this->textures["ENEMY"].loadFromFile("assets/placeholder.png"))
        std::printf("ERROR ENEMY TEXTURE NOT LOADED IN!\n");
    if(!this->bgTexture.loadFromFile("assets/prototype_background_big.png"))
        std::printf("ERROR BG TEXTURE NOT LOADED IN MENU!\n");

}

void BattleState::initEntities() {
    this->player.createSprite(&textures["PLAYER"], 0.7, 0.7);
    this->player.setPosition(1280.0/2 + 100,175);
    this->player.createStatsComponent(1, rd);

    this->spawnEnemy();
    this->player.update();
    this->enemy.update();
    this->setInitiative();


}

/*----------Functions-------------------*/

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

    this->scoreManager->updateScores(scoreCount);
}

void BattleState::spawnEnemy() {
    this->enemy.createSprite(&textures["ENEMY"], -0.7, 0.7 );
    this->enemy.setPosition(1280.0/2 - 100,175);
    this->enemy.createStatsComponent(1, rd);
}

//Battle
void BattleState::setInitiative()  {
    if(this->player.statsComponent->speed >= this->enemy.statsComponent->speed ) {
        player.statsComponent->hasTurn = true;

        std::cout << "PLAYER starts." << std::endl;

    }
    else{
        enemy.statsComponent->hasTurn = true;

        infoText.setString("The enemy starts.");
    }


}

void BattleState::battle() {

    if(this->player.statsComponent->hasTurn){
        this->playerTurn();

    }
    else
        this->enemyTurn();


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
                quit();
            }


}

void BattleState::enemyTurn(){
    using namespace std::chrono_literals;
    std::uniform_int_distribution<int> distLow(0,2);

    if(this->enemy.statsComponent->hasTurn){

        this->infoText.setString("It's the enemy's turn");
        updateUI();
        std::this_thread::sleep_for(0.5s);

        switch(distLow(rd)) {
            case PASS:
                this->infoText.setString("The enemy stares at you, menacingly.");
                updateUI();
                std::this_thread::sleep_for(0.5s);
                this->player.statsComponent->hasTurn = true;
                this->enemy.statsComponent->hasTurn = false;
                break;

            case HEAL:
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
    this->wonText.setString("You won! \n" + scoreStream.str() + "\n+101 Round Bonus!");
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

//Updates
void BattleState::update() {
    //Update Mouse Position
    this->attackButton.update(*mousePosView);
    this->healButton.update(*mousePosView);
    this->quitButton.update(*mousePosView);
    this->continueButton.update(*mousePosView);
    this->exitButton.update(*mousePosView);

    this->battle();



}

void BattleState::updateUI() {
    // Update Score
    this->scoreStream.str(std::string());
    this->scoreStream << "Score: " << this->scoreCount;
    this->scoreText.setString(scoreStream.str());

    // Update Round
    this->roundStream.str(std::string());
    this->roundStream << "Round: " << this->roundCount;
    this->roundText.setString(roundStream.str());

    updateStatInfo();

}

void BattleState::updateStatInfo() {
    this->pStats.str(std::string());
    this->eStats.str(std::string());


    this->pStats << "PLAYER LV: " << this->player.statsComponent->level << "\n"
                 << "HEALTH: " << this->player.statsComponent->hp << " / " <<  this->player.statsComponent->hpMax
                 << "   HEALS: " << this->player.statsComponent->heals << " / " << "3" << "\n"
                 <<"ATK: " << this->player.statsComponent->atk
                 << "   DEF: " << this->player.statsComponent->def;

    this->eStats << "ENEMY LV: " << this->enemy.statsComponent->level << "\n"
                 << "HEALTH: " << this->enemy.statsComponent->hp << " / "<<  this->enemy.statsComponent->hpMax
                 << "   HEALS: " << this->enemy.statsComponent->heals << " / " << "3" << "\n"
                 << "ATK: " << this->enemy.statsComponent->atk
                 << "    DEF: " << this->enemy.statsComponent->def;

    this->statInfoP.setString(pStats.str());
    this->statInfoE.setString(eStats.str());

}




