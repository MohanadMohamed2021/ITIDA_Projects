pipeline {
    agent any

    stages {
        stage("remove all") {
            steps {
                script {
                    sh 'rm -rf *'
                }
            }
        }

        stage("make directory") {
            steps {
                script {
                    dir('pipe_line') {
                        sh 'mkdir -p pipe_line'
                    }
                }
            }
        }

        stage("make file") {
            steps {
                script {
                    dir('pipe_line') {
                        sh 'echo "hello world" > file'
                    }
                }
            }
        }
    }
}
