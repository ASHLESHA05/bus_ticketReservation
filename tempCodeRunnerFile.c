#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

Font font;		//logo and in-game font
int score=-1;
struct borders					// defines arena walls	(simple linked list)
{
	RectangleShape rect;
	struct borders *next;
	FloatRect boundingBox;
};
struct borders* btemp=NULL;

struct snake			//snake is a doubly linked list
{
	float x;	// direction of movement along x axis
	float y;	// direction of movement along y axis
	struct snake *next;
	struct snake *prev;
	RectangleShape rectangle;
	FloatRect boundingBox;
};

struct snake *top=NULL;		//tail of snake
struct snake *last=NULL;	//head of snake
struct snake* temp1=NULL;

struct movement			//	queue to store direction of movement
{
	float a,b;
	struct movement* next;
};
 
struct movement* first=NULL;	//top of the queue
struct movement* temp=NULL;

void construct_borders()		
{
	struct borders *rect1= new borders;
	struct borders *rect2= new borders;
	struct borders *rect3= new borders;
	struct borders *rect4= new borders;

	rect1->rect.setSize(Vector2f(20,410));
	rect2->rect.setSize(Vector2f(470,10));
	rect3->rect.setSize(Vector2f(470,10));
	rect4->rect.setSize(Vector2f(20,410));

	rect1->rect.setFillColor(Color::White);rect2->rect.setFillColor(Color::White);rect3->rect.setFillColor(Color::White);rect4->rect.setFillColor(Color::White);
	rect1->rect.setPosition(10,70);rect2->rect.setPosition(10,70);rect3->rect.setPosition(10,470);rect4->rect.setPosition(470,70);

	rect1->next=rect2;
	rect2->next=rect3; 
	rect3->next=rect4;
	rect4->next=NULL;
	
	btemp=rect1;
}

void insert(RenderWindow *window, bool *status, Text &text)			//make the snake grow
{	
	*status=false;													
	struct snake *p= new snake;
	p->rectangle.setSize(Vector2f(10,10));
	p->rectangle.setOutlineThickness(-1);
	p->rectangle.setOutlineColor(Color::Black);
		
	if (top==NULL)
	{
		p->rectangle.setFillColor(Color::Green);
		p->rectangle.setPosition(240,240);
		top=p;
		last=p;
		p->next=NULL;
		p->prev=NULL;
		p->x=0; p->y=-10;			//initial direction of movement
		temp1=p;
		
		window->clear(Color::Black); window->draw(p->rectangle); window->display();
		
	}
	else
	{       
			p->rectangle.setFillColor(Color(0,140,0));
			p->next=temp1;
			p->prev=last;
			p->x=temp1->x;		//follow the direction of previous node
			p->y=temp1->y;
			top=p;
			temp1->prev=p;
			Vector2f position=temp1->rectangle.getPosition();
			position.y=((-temp1->y)+position.y);		//set the position with respect to previous node's direction of movement and position
			position.x=((-temp1->x)+position.x);
			p->rectangle.setPosition(position);
			 window->clear(Color::Black);
			
			 struct snake* temp3;
				temp3=last;			// after insertion of new node the snake is redrawn node by node
				do{	
					window->draw(temp3->rectangle);
					temp3=temp3->prev;
					
				   }while(temp3!=last);	


				struct borders *t=btemp;		// re-draws walls
		do {
		window->draw(t->rect);
		t=t->next;
		}while(t!=NULL); 
		window->draw(text);				//re-draw score
			window->display();
			
			temp1=p;
			
	}
	

}

void update_score(Text &score1)
{
	score++;
	ostringstream ss;			//conversion from int to string for display on window
	ss << score;
	string str = ss.str();
	
		score1.setFont(font);
		score1.setCharacterSize(40);
		score1.setPosition(200,10);
		score1.setColor(sf::Color::White);
		score1.setString(str);
		
	
}

void insert_movement(float a, float b)  // queue node is created to save every keystroke
{
	if ((last->x!=-a)||(last->y!=-b))			//check to prevent snake head from moving in the opposite direct and crashing into itself
	{
	struct movement* n=new movement;
	n->a=a; n->b=b;
	n->next=NULL;
	if (first==NULL)
	{
		temp=n;
		first=n;
	}
	else
	{
		temp->next=n;
		temp=n;
		
	}
	}

}

void remove_movement()				// queue node is removed after snake head has turned
{
	struct movement* temp2=first;
	struct movement* temp3=first->next;

	
	if(first->next!=NULL)
	{
	first->next=temp3->next;
	first=temp3;
	free(temp2);
	}
	else
	{
		free(first);
		first=NULL;
	}
}


Vector2f generate_random()		//generate random positions for food 
{
	if(score==0)
	srand(time(NULL));		//seeding the random function only once
	
	float x= (31+rand() % 428);
	 float y= (81+rand() % 383);
	 Vector2f position;
	 position.x=x; position.y=y;

	 CircleShape dummy(4); 
	 dummy.setPosition(position);
	 FloatRect bb=dummy.getGlobalBounds();
	
	struct snake* temp3=last;			//check if food position is not occupied by snake
				do{	
					temp3->boundingBox=temp3->rectangle.getGlobalBounds();
					
					if(temp3->boundingBox.intersects(bb))
					position=generate_random();
					temp3=temp3->prev;
					
				   }while(temp3!=last);	
				

		return position;
    
}
CircleShape food(4);

void generate_food()
{
	food.setPosition(generate_random());
	food.setFillColor(Color::Yellow);
}

void draw_all(RenderWindow *window,Text *score2,Text *score3)
{	
	struct borders *t=btemp;		// draw walls
	do {
		window->draw(t->rect);
		t=t->next;
		}while(t!=NULL); 

	window->draw(food);
	window->draw(*score3);			//draw "score"
	window->draw(*score2);			//draw score(integers)

	struct snake *temp5=last;		//draw and move each snake node
		do
		{
			
			temp5->rectangle.move(temp5->x,temp5->y);		
			window->draw(temp5->rectangle);
			temp5=temp5->prev;
			
		}while(temp5!=last);

}

bool collision_check(bool *status)
{	
	FloatRect boundingBox1=last->rectangle.getGlobalBounds();	// snake head's bounding box
	FloatRect boundingBox2=food.getGlobalBounds();			//food's bounding box

	if (boundingBox2.intersects(boundingBox1))
	{generate_food(); *status=true;}

	struct snake *temp5=last->prev;					
		do
		{
			temp5->boundingBox=temp5->rectangle.getGlobalBounds();		//check if snake has crashed into itself
		if (temp5->boundingBox.intersects(boundingBox1))
		  return true;
				temp5=temp5->prev;
			
		}while(temp5!=last);

	struct borders *t=btemp;
	do {
		t->boundingBox=t->rect.getGlobalBounds();				//check if snake has crashed into a wall
		if (t->boundingBox.intersects(boundingBox1))
			  return true;
		t=t->next;
		}while(t!=NULL); 
}

void moving(RenderWindow *window)			//movement thread. makes sure snake nodes turn only after its previous node has turned
{
		construct_borders();
		Text text;
		text.setFont(font); 
		text.setString("Game Over");
		text.setCharacterSize(40);
		text.setPosition(275,10);
		text.setColor(Color(255,0,51));

		Text mytext;
		mytext.setFont(font);
		mytext.setString("Score: ");
		mytext.setCharacterSize(40);
		mytext.setPosition(20,10);

		Text score2;
		update_score(score2);
			
		bool collision=false;				//collision turns true when snake collides with itself/wall. status remains false
		bool status=false;					//status turns true when snake collides with food. collision remains false
		
		
		insert(window,&status,mytext);		//intialize snake
		insert(window,&status,mytext);
		insert(window,&status,mytext);
		insert(window,&status,mytext);
		
		generate_food();
		

	while(window->isOpen())
	{
		struct snake *temp4=top;
		struct snake *previous=temp4->next;
		
		if(first!=NULL)			
		{
			last->x=first->a;	// assign head of snake movement direction corresponding to first node of queue. 
			last->y=first->b;
			remove_movement();
		}
			
		
		window->clear(Color::Black);
		draw_all(window,&score2,&mytext);
		window->display();
		collision=collision_check(&status);

		if (status==true)
			{
				insert(window,&status,mytext);
				update_score(score2);
			}
			
		
		if (collision==true)
		{
			window->draw(text);
			window->display();
			break;
		}
		sleep(seconds(0.1f));
	
		do {
		temp4->x=previous->x;
		temp4->y=previous->y;
		temp4=temp4->next;
		previous=previous->next;
		}while(temp4!=last);
}
}

void title_screen(RenderWindow *window)
{
	Font font1;
	if (!font.loadFromFile("brokenstick.ttf"))
			   cout<<"blahblah error"<<endl;
	if (!font1.loadFromFile("BRLNSR.ttf"))
	  cout<<"blahblah error"<<endl;
	
	Texture logo;
	if (!logo.loadFromFile("k11766153.png"))
    cout<<"blahblah error"<<endl;
	
	Sprite sprite;
	sprite.setTexture(logo);
	sprite.setPosition(165,30);
	sprite.setColor(Color(0,240,0));

Text snake1;
snake1.setFont(font);
snake1.setString("Snake");
snake1.setCharacterSize(50); 
snake1.setColor(Color(0,230,0));
snake1.setPosition(185,164);

Text text;
text.setFont(font1);
text.setString("Created By: ");
text.setCharacterSize(30); 
text.setColor(Color(255,255,51));
text.setStyle(Text::Bold);
text.setPosition(175,230);

Text text2;
text2.setFont(font1);
text2.setString("Ayesha Waheed-040\nDaniya Asim-041\nKomal Mariam-046\nMaryam Atiq-076");
text2.setCharacterSize(24); 
text2.setColor(Color(0,255,255));
text2.setPosition(157,270);
	
	window->clear(Color::Black);
	window->draw(sprite);
	window->draw(snake1);
	window->draw(text);
	window->draw(text2);
	window->display();
	sleep(seconds(4));
}

void main()
{
	RenderWindow window(VideoMode(500,500),"Snake Game");
	window.setVerticalSyncEnabled(true);		//application runs at same frequency as monitor (60 frames/second)
	window.setKeyRepeatEnabled(false);			//halts generation of multiple events when a key is pressed once and held

	title_screen(&window);
	
	window.setActive(false);					//	main thread releases command of window  
	Thread thread(&moving,&window);				//transferring command to second moving thread
	thread.launch();
	
	Event event;
	
	while (window.isOpen())
	{
		while(window.pollEvent(event))
	{
		switch (event.type)
    {
           case Event::Closed:
            window.close();
            break;
       
        case Event::KeyPressed:
			{
				
				if(Keyboard::isKeyPressed(Keyboard::Left))
					insert_movement(-10,0);
									
				if(Keyboard::isKeyPressed(Keyboard::Right))
					 insert_movement(10,0);
											
				if(Keyboard::isKeyPressed(Keyboard::Up))
					insert_movement(0,-10);
						
				if(Keyboard::isKeyPressed(Keyboard::Down))
					insert_movement(0,10);
					break;
        
			}
		}
	}
	}
    
}