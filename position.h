#ifndef POSITION_H
#define POSITION_H

class Position{
		
	int x;
	int y;	
	
public: 
	
	Position(int x, int y);
	int getX() const;
	int getY() const;
	void setX(int val);
	void setY(int val);
	bool equals(Position pos) const;
	bool isValid() const;
 
};
#endif
