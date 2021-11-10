#pragma once

#include <vector>
#include "eveniment.h"

class evenimentColectiv : public eveniment
{
protected:
    vector<string> participanti;
public:
    evenimentColectiv();
    friend istream& operator>>(istream&, evenimentColectiv&);
    friend ostream& operator<<(ostream&, const evenimentColectiv);


};


