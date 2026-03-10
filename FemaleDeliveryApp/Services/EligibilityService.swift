import Foundation

struct EligibilityService {
    func validateUserAccess(
        gender: Gender,
        country: SupportedCountry,
        platform: AppPlatform
    ) -> Result<Void, String> {
        let config = PlatformRegistry.config(for: platform)

        guard config.supports(country: country) else {
            return .failure("Service is currently unavailable in \(country.displayName) on \(platform.displayName).")
        }

        guard gender == .female else {
            return .failure("This app is available only for female users.")
        }

        return .success(())
    }
}
