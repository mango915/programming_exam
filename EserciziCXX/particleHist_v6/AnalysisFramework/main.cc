#include "AnalysisFactory.h"
#include "AnalysisInfo.h"
#include "Dispatcher.h"
#include "EventSource.h"
#include "SourceFactory.h"

using namespace std;

int main(int argc, char *argv[]) {

  // store command line parameters
  AnalysisInfo *info = new AnalysisInfo(argc, argv);

  // create data source
  EventSource *event_source = SourceFactory::create(info);

  // create a list of analyzers
  AnalysisFactory::create(info);

  // initialize all analyzers
  Dispatcher<AnalysisInfo::AnalysisStatus>::notify(AnalysisInfo::begin);

  // loop over events
  event_source->run();

  // finalize all analyzers
  Dispatcher<AnalysisInfo::AnalysisStatus>::notify(AnalysisInfo::end);

  return 0;
}
