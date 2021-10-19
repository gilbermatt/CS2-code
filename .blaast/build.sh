#!/bin/bash
set -euo pipefail

APP_NAME="blaast-template-base"
BUILDER_IMAGE="gcr.io/shopify-docker-images/apps/production/google-buildpacks-private:latest"
IMG_BASE="gcr.io/shopify-docker-images/apps/production/blaast-template-base"
IMG_TAG="${BUILDKITE_COMMIT:-latest}"

main() {
  publish_flag=""

  echo "--- pre-fetch app image, if applicable"
  docker pull "${IMG_BASE}:latest" || true # cool if we can't find it

  echo "--- buildpack build with pack utility"
  if [ "${BUILDKITE_BRANCH:-}" == "master" ]; then publish_flag="--publish"; fi

  pack build "${IMG_BASE}:${IMG_TAG}" "${publish_flag}" \
    --builder ${BUILDER_IMAGE} \
    --env GOOGLE_FUNCTION_TARGET="${APP_NAME}" \
    --env BUNDLE_PACKAGES__SHOPIFY__IO="${BUNDLE_PACKAGES__SHOPIFY__IO}" \
    --verbose
  }

main "$@"
