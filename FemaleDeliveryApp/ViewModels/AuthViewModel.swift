import Foundation

@MainActor
final class AuthViewModel: ObservableObject {
    @Published var currentUser: UserProfile?
    @Published var errorMessage: String?
    @Published var selectedPlatform: AppPlatform = .ios

    private let eligibilityService = EligibilityService()

    var isLoggedIn: Bool {
        currentUser != nil
    }

    func register(
        fullName: String,
        email: String,
        country: SupportedCountry,
        gender: Gender,
        platform: AppPlatform
    ) {
        errorMessage = nil

        switch eligibilityService.validateUserAccess(gender: gender, country: country, platform: platform) {
        case .success:
            currentUser = UserProfile(
                fullName: fullName,
                email: email,
                country: country,
                gender: gender,
                platform: platform,
                isVerifiedFemale: true
            )
        case let .failure(reason):
            errorMessage = reason
            currentUser = nil
        }
    }

    func signOut() {
        currentUser = nil
        errorMessage = nil
    }
}
