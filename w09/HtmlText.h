#ifndef SENECA_HTMLTEXT_H__
#define SENECA_HTMLTEXT_H__
#include "Text.h"
namespace seneca {
class HtmlText : public Text {
  char *m_title;

  void setTitle(const char *title);

public:
  HtmlText(const char *filename = nullptr, const char *title = nullptr);

  // copy constructor
  HtmlText(const HtmlText &);

  ~HtmlText();

  // copy assignment
  HtmlText &operator=(const HtmlText &);

  void write(std::ostream &os) const override;
};
} // namespace seneca
#endif // !SENECA_HTMLTEXT_H__
