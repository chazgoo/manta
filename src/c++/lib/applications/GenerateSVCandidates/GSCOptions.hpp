//
// Manta - Structural Variant and Indel Caller
// Copyright (c) 2013-2019 Illumina, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//

/// \file
/// \author Chris Saunders
///

#pragma once

#include "EdgeOptions.hpp"
#include "common/Program.hpp"
#include "options/AlignmentFileOptions.hpp"
#include "options/CallOptionsDiploid.hpp"
#include "options/CallOptionsShared.hpp"
#include "options/CallOptionsSomatic.hpp"
#include "options/CallOptionsTumor.hpp"
#include "options/ReadScannerOptions.hpp"
#include "options/SVRefinerOptions.hpp"

#include <string>
#include <vector>

struct GSCOptions {
  bool isSomatic() const { return (!somaticOutputFilename.empty()); }

  bool isTumorOnly() const { return (!tumorOutputFilename.empty()); }

  bool isGenerateEvidenceBam() const { return (!evidenceBamStub.empty()); }

  AlignmentFileOptions alignFileOpt;
  EdgeOptions          edgeOpt;
  ReadScannerOptions   scanOpt;
  SVRefinerOptions     refineOpt;
  CallOptionsShared    callOpt;
  CallOptionsDiploid   diploidOpt;
  CallOptionsSomatic   somaticOpt;
  CallOptionsTumor     tumorOpt;

  int workerThreadCount = 1;

  std::string graphFilename;
  std::string referenceFilename;
  std::string statsFilename;
  std::string chromDepthFilename;
  std::string edgeRuntimeFilename;
  std::string edgeStatsFilename;
  std::string edgeStatsReportFilename;

  std::string candidateOutputFilename;
  std::string diploidOutputFilename;
  std::string somaticOutputFilename;
  std::string tumorOutputFilename;
  std::string rnaOutputFilename;
  std::string evidenceBamStub;

  bool isVerbose = false;  ///< provide some high-level log info to assist in debugging

  bool isSkipAssembly =
      false;  ///< if true, skip assembly and run a low-resolution, breakdancer-like subset of the workflow

  bool isSkipScoring = false;  ///< if true, skip quality scoring and output candidates only

  bool enableRemoteReadRetrieval =
      false;  ///< if true, turn on retrieval of poorly mapped remote reads for assembly

  bool isRNA = false;  ///< if true, RNA specific filtering on candidates and diploid scoring is used

  bool isUnstrandedRNA = false;  ///< For unstranded RNA data, the direction of fusion transcripts is unknown

  unsigned minCandidateSpanningCount =
      3;  ///< how many spanning evidence observations are required to become a candidate?

  unsigned minScoredVariantSize =
      50;  ///< min size for scoring and scored output following candidate generation

  bool isOutputContig = false;  ///< if true, an assembled contig is written in VCF
};

void parseGSCOptions(const illumina::Program& prog, int argc, char* argv[], GSCOptions& opt);