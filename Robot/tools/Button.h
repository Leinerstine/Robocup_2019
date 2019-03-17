#ifndef _BUTTON_H_
#define _BUTTON_H_


class Button
{

  int m_Pin;
  bool m_bWasDownLastFrame;
  bool m_bIsReleasedThisFrame;
  bool m_bIsPressedThisFrame;

  public:
  Button(int _pin)
  {
    m_Pin = _pin;
    m_bWasDownLastFrame = false;
    m_bIsPressedThisFrame = false; 
    m_bIsReleasedThisFrame = false;
  }

  bool IsPressed() const
  {
    return m_bIsPressedThisFrame;
  }
  bool IsReleased() const
  {
    return m_bIsReleasedThisFrame;
  }

  void Update()
  {
    int b = digitalRead(m_Pin);
    m_bIsReleasedThisFrame = false;
    m_bIsPressedThisFrame = false;
    
    if (b==1)
    {
      if (!m_bWasDownLastFrame)
        m_bIsPressedThisFrame = true;
      
      m_bWasDownLastFrame = true;
    }
    else
    {
      if (m_bWasDownLastFrame)
        m_bIsReleasedThisFrame = true;

       m_bWasDownLastFrame = false;
    }
  }
};

#endif //_BUTTON_H_
