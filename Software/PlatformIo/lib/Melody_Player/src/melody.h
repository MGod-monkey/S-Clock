#ifndef MELODY_H
#define MELODY_H

#include <Arduino.h>
#include <memory>

/**
 * A note and the relative duration. 
 */
struct NoteDuration {
  // the frequency of a note
  unsigned short frequency;
  // duration of the frequency, expressed as number of "time unit"
  unsigned short duration;
};

/**
 * This class stores the data to play a melody. 
 * To eases the creation of a melody, you may use MelodyFactory class.
 */
class Melody {
public:
  Melody():
   notes(nullptr) {};
  
  Melody(String title, unsigned short timeUnit, std::shared_ptr<std::vector<NoteDuration>> notes, bool automaticSilence):
    title(title), timeUnit(timeUnit), notes(notes), automaticSilence(automaticSilence) {};

  /**
   * Return the title of the melody.
   */
  String getTitle() const {
    return title;
  };

  /**
   * Return the base time unit (i.e. the shortest possible
   * note in this melody), expressed in millisecond.
   */ 
  unsigned short getTimeUnit() const {
    return timeUnit;
  };

  /**
   * Get number of notes.
   */
  unsigned short getLength() const {
    if(notes == nullptr) return 0;
    return (*notes).size();
  }

  /**
   * Get a note at a given position.
   * Check length or validity of melody before call this method.
   */
  NoteDuration getNote(unsigned short i) const {
    if(i < (*notes).size()) {
      return (*notes)[i];
    }
    return (*notes).back();
  };

  bool getAutomaticSilence() const {
    return automaticSilence;
  }

  /**
   * Tell if the object contains a valid melody.
   */
  bool isValid() const {
    return notes != nullptr && (*notes).size() != 0;
  }

  /**
   * Return true if contains a valid melody, false otherwise.
   */
  explicit operator bool() const {
    return isValid();
  }
  
private:
  String title;
  unsigned short timeUnit;
  std::shared_ptr<std::vector<NoteDuration>> notes;
  const static unsigned short maxLength = 1000;
  bool automaticSilence;
  
  const static bool debug = false;
};

#endif // END MELODY_H
