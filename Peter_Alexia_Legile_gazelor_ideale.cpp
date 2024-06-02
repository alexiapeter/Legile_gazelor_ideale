#include <graphics.h>
#include <stdio.h>
#include <math.h>


float V;          // numar de moli
int i;           // grad de libertate a gazului
float Cv, Cp;   // caldura la presiune si volum constant 
float R = 8.31;// constanta universala a gazului ideal J/mol*K  
    
void izobara (float Pa, float Ta, float Tb, float Va, float Vb, float *Q, float *W, float *DU)
{
   *Q = V * Cp * (Tb-Ta);
   *W = Pa *1000* (Vb-Va);
   *DU = V * Cv * (Tb-Ta); 
   
   printf("\nTransformarea izobara: \n\tCaldura: %.2f J/(mol*K) \n\tLucru mecanic: %.2f J\n\tVariatia energiei interne: %.2f J \n ........ %.4f %.4f %.4f %.4f %.4f\n  ", *Q, *W, *DU, Pa, Ta, Tb, Va, Vb );
}
void izocora (float Ta, float Tb, float *Q , float *W, float *DU)
{
   *Q = V * Cv * (Tb-Ta);
   *W = 0;
   *DU = V * Cv * (Tb- Ta); 
    printf("\nTransformarea izocora: \n\tCaldura: %.2f J/(mol*K)\n\tLucru mecanic: %.2f J\n\tVariatia energiei interne: %.2f J \n ........ %.4f %.4f \n  ", *Q, *W, *DU,  Ta, Tb );
}
void izoterma(float Ta, float Va, float Vb, float *Q, float *W, float *DU)
{
  *Q = V * R * Ta * log(Vb/Va);
  *W = V * R * Ta * log(Vb/Va);
  *DU = 0; 
   printf("\nTransformarea izoterma: \n\tCaldura: %.2f J/(mol*K)\n\tLucru mecanic: %.2f J\n\tVariatia energiei interne: %.2f J\n........ %.4f %.4f %.4f \n ", *Q, *W, *DU, Ta, Va, Vb );
}

int main()
{
    float P1, V1, T1;
    float P2, V2, T2;
    float P3, V3, T3;

    printf("Introduceti gradul de libertate a gazului: ");
    scanf("%d", &i);
        while(i != 3 && i != 5){
            printf("Valoare invalida!\nIntroduceti din nou gradul de libertate a gazului:\n");
        scanf("%d", &i);
    }

    printf("Introduceti numarul de moli: ");
    scanf("%f", &V);
        while(V<=0){
            printf("Valoare invalida\nIntroduceti numarul de moli: \n");
        scanf("%f", &V);
        }
		        
    Cp= (i+2)*R/2;
	Cv= (i*R)/2; 
    printf("Caldura molara la presiune constanta: %.2f J/(mol*K) .\n", Cp);
    printf("Caldura molara la volum constant: %.2f J/(mol*K) . \n", Cv);
        
    printf("Introduceti parametrii sistemului pentru starile 1, 2, 3: (p v t) \n");
    printf("[1]: ");
    scanf("%f%f%f", &P1, &V1, &T1);
    while(P1*T1<0 || T1*V1<0 || V1*P1<0 || P1*V1*T1<0){
        printf("Una sau mai multe valori invalide!\n");
        printf("[1]: ");
        scanf("%f %f %f", &P1, &V1, &T1);
    }
    
    printf("[2]: ");
    scanf("%f%f%f", &P2, &V2, &T2);
    while(P2*T2<0 || T2*V2<0 || V2*P2<0 || P2*V2*T2<0){
        printf("Una sau mai multe valori invalide!\n");
        printf("[2]: ");
        scanf("%f %f %f", &P2, &V2, &T2);
    }
    
    printf("[3]: ");
	 scanf("%f%f%f", &P3, &V3, &T3);
    while(P3*T3<0 || T3*V3<0 || V3*P3<0 || P3*V3*T3<0){
        printf("Una sau mai multe valori invalide!\n");
        printf("[3]: ");
        scanf("%f %f %f", &P3, &V3, &T3);
    }
   float Qc=0.0, Qp=0.0, Wt=0.0, DUt=0.0;
   float Q1=0.0, W1=0.0, DU1=0.0;
   float Q2=0.0, W2=0.0, DU2=0.0;
   float Q3=0.0, W3=0.0, DU3=0.0;
   
    //Transfomarea 1-2
   int izoterma_1_2 = 0;
   if( P1 == P2 )
   {
     izobara(P1, T1, T2, V1, V2, &Q1, &W1, &DU1);
   }
   else if(V1 == V2)
         {
            izocora(T1, T2, &Q1, &W1, &DU1);
         }
	   else if(T1 == T2)
	       {
	        izoterma(T1, V1, V2, &Q1, &W1, &DU1 );
	        izoterma_1_2 = 1;
	       }
	

    //Transfomarea 2-3
   int izoterma_2_3 = 0;
   if( P2 == P3 )
   {
       izobara(P2, T2, T3, V2, V3, &Q2, &W2, &DU2);
   }
   else if(V2 == V3)
      {
        izocora(T2, T3, &Q2, &W2, &DU2);
	  }
	  else if(T2 == T3)
	  {
	    izoterma(T2, V2, V3, &Q2, &W2, &DU2 );
	    izoterma_2_3 = 1;
	  }
	
    //Transfomarea 3-1
   int izoterma_3_1 = 0; 
   if( P3 == P1 )
   {
       izobara(P3, T3, T1, V3, V1, &Q3, &W3, &DU3);
   }
   else if(V3 == V1)
      {
        izocora(T3, T1, &Q3, &W3, &DU3);
	  }
	  else if(T3 == T1)
	  {
	    izoterma(T3, V3, V1, &Q3, &W3, &DU3 );
	    izoterma_3_1 = 1;
	  }
	

  
    if(Q1>0)
       Qp = Qp + Q1;
    else 
	   Qc = Qc +Q1;
	   
	if(Q2>0)
       Qp = Qp + Q2;
    else 
	   Qc = Qc +Q2;
	   
	if(Q3>0)
       Qp = Qp + Q3;
    else 
	   Qc = Qc +Q3;      
	
    printf("Caldura cedata in timpul transformarilor este : %.2f J.\n", Qc);
    printf("Caldura primita in timpul transformarilor este : %.2f J.\n", Qp);

    //Grafic:
	int gr=DETECT,gm;
	initgraph(&gr,&gm,(char*)"");
	
	double put_x,put_y,t;
 	int leftMargin = 10; 
    int topMargin = 10; 
    int arrowSize = 8; 

    // Axa Oy
    line(leftMargin, 0, leftMargin, getmaxy());
    line(leftMargin, getmaxy(), leftMargin - arrowSize, getmaxy() - arrowSize);
    line(leftMargin, getmaxy(), leftMargin + arrowSize, getmaxy() - arrowSize);
    outtextxy(leftMargin + 5, getmaxy() - 20, "Y-P*10^3(N/m^2)");

    // Axa Ox
    line(0, topMargin, getmaxx(), topMargin);
    line(getmaxx(), topMargin, getmaxx() - arrowSize, topMargin - arrowSize);
    line(getmaxx(), topMargin, getmaxx() - arrowSize, topMargin + arrowSize);
    outtextxy(getmaxx() - 70, topMargin + 10, "X-V(m^3)");

	double GX, GY ;

	 GY = (P1+P2+P3)/3;
	 GX = (V1+V2+V3)/3;
	 
	
  if(izoterma_1_2 == 1  )   // x - v     y =  p
  {
	for(t=0.0;t<=1.0;t=t+0.001)           
	{
	put_y = pow(1-t,3)*P1 + 3*t*pow(1-t,2)*P1 + 3*t*t*(1-t)*GY + pow(t,3)*P2; // Formula to draw curve
	put_x =  pow(1-t,3)*V1 + 3*t*pow(1-t,2)*V1 + 3*t*t*(1-t)*GX + pow(t,3)*V2;
	putpixel(put_x,put_y, WHITE);            // putting pixel 
	}
  }
  else 
	{
   		line(V1, P1, V2, P2);
	}
  
  if(izoterma_2_3 == 1  )
  {
	for(t=0.0;t<=1.0;t=t+0.001)           
	{
	put_y = pow(1-t,3)*P2 + 3*t*pow(1-t,2)*P2 + 3*t*t*(1-t)*GY + pow(t,3)*P3; // Formula to draw curve
	put_x =  pow(1-t,3)*V2 + 3*t*pow(1-t,2)*V2 + 3*t*t*(1-t)*GX + pow(t,3)*V3;
	putpixel(put_x,put_y, WHITE);            // putting pixel 
	}
  }
  else 
	{
      line(V2, P2, V3, P3);
	}
  
  if(izoterma_3_1 == 1 )
  {
	for(t=0.0;t<=1.0;t=t+0.001)          
	{
	put_y = pow(1-t,3)*P3 + 3*t*pow(1-t,2)*P3 + 3*t*t*(1-t)*GY + pow(t,3)*P1; // Formula to draw curve
	put_x =  pow(1-t,3)*V3 + 3*t*pow(1-t,2)*V3 + 3*t*t*(1-t)*GX + pow(t,3)*V1;
	putpixel(put_x,put_y, WHITE);            // putting pixel 
	}
  }
  else 
	{
   		line(V3, P3, V1, P1);
	}
     	
     	
    getch();
    closegraph();

	return 0;
}
