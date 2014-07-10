//THIS DOESNT EXACTLY WORK YET. DONT EXPECT TO UPLOAD IT AND HAVE IT RUN.
//ARUINO FUEL INJECTOR CLEANER/TESTER

//refactored by Keith Vasilakes
//To simplify things
//July 10 2014

uint8_t Injector[8];
 
uint8_t injqty;
uint32_t OnTime;
uint32_t StartTime;
int currentInjector;

 
void setup(void) 
{
    int i;
    
//not looping here so initialization can be done non sequentially if necessary
    Injector[0] = 5;
    Injector[1] = 6;
    Injector[2] = 7;
    Injector[3] = 8;
    
    Injector[4] = 9;
    Injector[5] = 10;
    Injector[6] = 11;
    Injector[7] = 12;
    
    //set initial state of the pins
    for( i=0; i< injqty; i++)
    {
        //make them all outputs
        pinMode(Injector[i], OUTPUT);
        
        //make sure they are all off
        Injector[i] = false;
    }
    
    //set up variables
    injqty = 8;
    currentInjector = 0;
    
    //how long an injector should be on
    OnTime = 1000ul;
    
    //turn on the first injector
    StartTime = micros();
    
    digitalWrite(Injector[currentInjector], true);
}

bool IsTimedOut(uint32_t period, uint32_t startTime)
{
    return (((uint32_t)(micros() - startTime)) > period ? true: false);
}
 
//turn on each injector one by one for the time specified
//All injectors are on for the same amout of time until the time is changed by the user 
void loop(void)
{
    //check if if it's time to turn off the current injector
    if(IsTimedOut(OnTime, StartTime))
    {
        //turn off current injector
        digitalWrite(Injector[currentInjector], false);
 
        //next injector
        currentInjector++;
        
        //rollover to first injector
        if(currentInjector >= injqty)
        {
            currentInjector = 0;
        }
        
        //turn on next injector
        digitalWrite(Injector[currentInjector], true);
        
        StartTime = micros();
    }
}
 

