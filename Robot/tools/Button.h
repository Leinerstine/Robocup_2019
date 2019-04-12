#ifndef _BUTTON_H_
#define _BUTTON_H_


class Button
{
  int m_Pin; //adresse du Pin
  bool m_bWasDownLastFrame; //était appuyé avant
  bool m_bIsReleasedThisFrame; //vient d'être relâché
  bool m_bIsPressedThisFrame; //appuyé à ce moment 
  long m_DownStartTime; //début du moment où il était appuyé 
  long m_FullPressedTime; //temps total où il était appuyé 

  public: //peut être utilisé à l'extérieur de la classe
  Button(int _pin) //initialisation 
  {
    m_Pin = _pin; 
    m_bWasDownLastFrame = false;
    m_bIsPressedThisFrame = false; 
    m_bIsReleasedThisFrame = false;
    m_DownStartTime = 0;
    m_FullPressedTime = 0;
  }

  bool IsPressed() const //si c'est appuyé renvoie que ça l'était
  {
    return m_bIsPressedThisFrame;
  }
  bool IsReleased() const //si c'est relâché renvoie que ça l'était
  {
    if (m_FullPressedTime < 500)
      return m_bIsReleasedThisFrame;
    return false; //pas relâché 
  }

  void Update()
  {
    int b = digitalRead(m_Pin); //regarde ce que renvoie le boutton
    m_bIsReleasedThisFrame = false; //à la base
    m_bIsPressedThisFrame = false;
    
    if (b==1) //1 = appuyé 
    {
      if (!m_bWasDownLastFrame) //s'il n'était pas appuyé avant
      {
        m_DownStartTime = millis(); //temps où il est appuyé 
        m_bIsPressedThisFrame = true; //mtnt vient d'être appuyé 
      }
      m_bWasDownLastFrame = true; //on modifie pour la prochaine boucle 
    }
    else //si pas appuyé 
    {
      if (m_bWasDownLastFrame) //déjà appuyé
      {
        m_bIsReleasedThisFrame = true; //maintenant relâché
        m_FullPressedTime = millis() - m_DownStartTime; //temps actuel moins le début où il était appuyé
      }
       m_bWasDownLastFrame = false; //quoi qu'il se passe pour la prochaine boucle, n'était pas appuyé avant 
    }
  }
};

#endif 